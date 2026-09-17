*This project has been created as part of the 42 curriculum by johiew*
# Born2beroot

## Description

Born2beroot is a 42 School system administration project. The goal is to set up a virtual machine running either **Debian** or **Rocky Linux**, without a graphical interface, configured according to strict security and administration rules. The project is meant to introduce core sysadmin concepts: virtualization, disk partitioning with LVM, user/group management, password policies, SSH hardening, firewall configuration, mandatory access control (AppArmor/SELinux), sudo logging, and a custom monitoring script broadcast via cron.

The end result is a hardened, minimal, headless Debian (or Rocky) server that can be administered remotely over SSH, with every privileged action logged and a live system-status message broadcast every 10 minutes.

**Bonus part** (only evaluated if the mandatory part is 100% correct): a second service stack on top of the base server — in this case a **WordPress** site running on **OpenLiteSpeed** with a **MariaDB** database.

---

## Project Description: Design Choices

### Operating system choice: Debian

This project uses **Debian**, not Rocky Linux.

| | Debian | Rocky Linux |
|---|---|---|
| Origin | Independent community project since 1993 | Community fork of RHEL, created 2021 after CentOS shifted to a rolling model |
| Package manager | APT / dpkg (`.deb`) | DNF / RPM (`.rpm`) |
| Release model | Stable releases every ~2 years, long testing cycles | Tracks RHEL releases 1:1 |
| Package freshness | Conservative, long-tested versions | Enterprise-focused, binary-compatible with RHEL |
| Default MAC system | AppArmor | SELinux |
| Typical use | General-purpose servers/desktops, base for Ubuntu | Enterprise servers needing RHEL compatibility |
| Advantages | Huge documentation/community, simpler AppArmor profiles, very lightweight minimal installs, widely used for learning | Free RHEL-equivalent, ideal if targeting real enterprise/production RHEL environments, long enterprise support lifecycle |
| Disadvantages | Less "enterprise-standard" in some corporate environments than RHEL-family systems | SELinux has a steeper learning curve, DNF ecosystem less universally documented for beginners |

**Reason for choosing Debian:** simpler package management for a first sysadmin project, lighter-weight minimal install, and AppArmor's path-based profiles are more approachable to learn and demonstrate than SELinux's label-based system.

### Partitioning & LVM

The disk uses **LVM (Logical Volume Manager)** with separate logical volumes rather than one large partition, for several reasons:

- **Isolation** — if `/var` (logs) or `/tmp` fills up, only that logical volume is affected; `/` and the rest of the system remain usable and bootable.
- **Different mount options per partition** — e.g. `/tmp` can be mounted `noexec,nosuid` to block execution of files planted there, which isn't possible with a single shared partition.
- **Independent management** — `/home` (user data) can be backed up, resized, or reinstalled independently of `/` (system) or `/var` (logs).
- **Flexibility** — the whole point of LVM is the ability to resize volumes later without repartitioning; a single giant LV would defeat much of that purpose.

Chain used: **disk → PV (Physical Volume) → VG (Volume Group) → LV (Logical Volume) → filesystem → mount point.**

Typical volumes created: `/`, `/home`, `/var`, `/var/log`, `/srv`, `/tmp`, and swap.

### Security policies

- **Password policy** (`/etc/login.defs` for new-user defaults, `chage` for existing users, `pam_pwquality` in `/etc/pam.d/common-password` for complexity):
  - Maximum password age, minimum password age (to prevent immediately reverting to an old password), and a warning period before expiry.
  - Minimum length and character-class complexity requirements.
  - **Why:** limits how long a compromised password stays valid, prevents trivial guessing/cracking, and closes the "change it back immediately" loophole — critical since sudo access is gated by this same password.
- **sudo configuration** (`/etc/sudoers.d/`):
  - `log_input` and `log_output` to capture full interactive sudo sessions.
  - `logfile` directive writing a plain-text audit trail to `/var/log/sudo/sudo.log`.
  - **Why:** ties every privileged action to a specific authenticated user, rather than a shared/anonymous root session.
- **SSH hardening** (`/etc/ssh/sshd_config`):
  - `Port 4242` instead of default 22 — reduces automated bot noise, but is **security through obscurity**, not real security.
  - `PermitRootLogin no` — forces login as a regular user + sudo, for accountability.
- **AppArmor** — Mandatory Access Control (MAC), enforced by the system regardless of file ownership, on top of normal Unix DAC permissions. Confines what specific programs (e.g. `sshd`) are allowed to touch, based on path-based profiles. Checked with `aa-status`.
- **UFW firewall** — only the custom SSH port (4242) allowed inbound by default; everything else denied. UFW is a friendly front-end that, on current Debian, uses **nftables** as its backend.

### User & group management

- A personal user is created, added to a custom group and to the `sudo` group.
- **Primary group**: one per user, default ownership for files they create (`id username`).
- **Secondary groups**: additional memberships granting extra permissions, like `sudo` (`groups username`).
- Root direct login disabled everywhere except local console/emergency use; day-to-day admin work goes through the regular user + `sudo`.

### Services installed

- `openssh-server` — remote administration, hardened as above.
- `ufw` — firewall.
- `apparmor` (+ `apparmor-utils`) — mandatory access control.
- `sudo` — privilege escalation with full I/O logging.
- `cron` — schedules the monitoring script.
- Bonus: `openlitespeed`, `mariadb-server`, `php` + PHP extensions, WordPress.

### Monitoring script (`monitoring.sh`)

Runs as **root**, scheduled via `crontab -e -u root` with `*/10 * * * * /path/to/monitoring.sh`, and broadcasts a system summary (architecture, physical/virtual CPUs, RAM usage, disk usage, CPU load, last boot, LVM use, active TCP connections, logged-in users, IP/MAC address, sudo command count) to all logged-in terminals using `wall`.

---

## Comparisons

### Debian vs Rocky Linux
See the table above under "Operating system choice." In short: Debian uses APT/dpkg and AppArmor and favors general-purpose/learning use; Rocky uses DNF/RPM and SELinux and favors RHEL-compatible enterprise environments.

### AppArmor vs SELinux
Both are **Mandatory Access Control (MAC)** systems — the system enforces access rules regardless of file ownership, layered on top of standard Unix DAC permissions.

- **AppArmor** (Debian/Ubuntu default): **path-based** — profiles reference specific file paths directly (e.g. "this binary may read/write these exact paths"). Simpler to write and reason about. Modes: enforce (blocks) or complain (logs only). Status: `aa-status`.
- **SELinux** (RHEL/Rocky/Fedora default): **label-based** — every file, process, and port gets a security label (context); policy defines which labels may interact with which. More granular and powerful (a file's rules follow it if moved), but significantly more complex to configure and debug. Status: `sestatus`.

### UFW vs firewalld
- **UFW (Uncomplicated Firewall)** — Debian/Ubuntu's default friendly front-end for firewall rules. Simple syntax (`ufw allow 4242/tcp`), and on current Debian its backend is **nftables** (the modern successor to iptables). Good for straightforward allow/deny rule sets.
- **firewalld** — RHEL/Rocky/Fedora's default, dynamic firewall manager. Uses the concept of **zones** (e.g. `public`, `home`, `internal`) that group interfaces/rules by trust level, and can reload rules without dropping active connections. More flexible for environments with multiple network interfaces needing different trust levels, but has a steeper learning curve than UFW's simple allow/deny model. Managed via `firewall-cmd`.

In short: UFW favors simplicity for a single, mostly-static rule set; firewalld favors flexibility for multi-zone, dynamically changing network environments — matching the same Debian-simplicity vs RHEL-enterprise-flexibility pattern seen elsewhere (APT vs DNF, AppArmor vs SELinux).

### VirtualBox vs UTM
- **VirtualBox** — a free, cross-platform (Windows/macOS/Linux) **Type 2 (hosted)** hypervisor from Oracle. Runs as an application on top of an existing host OS. Mature, widely documented, supports both x86 and (with more limited/slower performance) ARM guests. The most common choice for this project on Windows/Linux hosts.
- **UTM** — a free, macOS-native **Type 2** hypervisor built on top of QEMU, with a Mac-friendly UI. Particularly well-suited to **Apple Silicon (M1/M2/M3)** Macs, since it can run ARM-native Linux guests at near-native speed, which VirtualBox struggles with on Apple Silicon.

In short: choose **VirtualBox** on Windows/Intel Macs/Linux hosts; choose **UTM** on Apple Silicon Macs for better performance with ARM guests.

---

## Instructions

### 1. Create the VM
1. Download the Debian netinst ISO (no desktop environment).
2. Create a new VM in VirtualBox/UTM: allocate disk space (subject usually specifies a minimum, e.g. 8–10GB split as required), RAM, and CPU cores.
3. Set the network adapter mode (NAT + port forwarding, or Bridged — see networking notes below).

### 2. Install Debian with LVM + encryption
1. Boot the ISO, choose the **manual/expert partitioning** option (not guided) so LVM can be configured explicitly.
2. Set up encrypted LVM if required by your subject (`Configure encrypted volumes` in the installer), then create the Volume Group and Logical Volumes: `/`, `/home`, `/var`, `/var/log`, `/srv`, `/tmp`, swap.
3. Do **not** install a desktop environment — deselect it during `tasksel`; install only "SSH server" and "standard system utilities."
4. Set hostname to your 42-login + "42" (e.g. `login42`) during install.

### 3. Post-install base configuration
```bash
apt update && apt upgrade
apt install sudo openssh-server ufw
```
- Create your personal user, add to a custom group and to `sudo`:
```bash
adduser username
addgroup customgroup
usermod -aG customgroup,sudo username
```
- Configure `/etc/ssh/sshd_config`:
```
Port 4242
PermitRootLogin no
```
```bash
sshd -t                  # validate before reload
systemctl reload ssh
```
- Configure UFW:
```bash
ufw allow 4242/tcp
ufw enable
ufw status verbose
```

### 4. Password policy
```bash
# /etc/login.defs — sets defaults for NEW users
PASS_MAX_DAYS   30
PASS_MIN_DAYS   2
PASS_WARN_AGE   7
```
For the existing user created above (login.defs doesn't retroactively apply):
```bash
chage -M 30 -m 2 -W 7 username
```
Enforce complexity via `pam_pwquality` in `/etc/pam.d/common-password` (minimum length, character variety, reject passwords similar to username).

### 5. sudo configuration & logging
```bash
mkdir -p /var/log/sudo
visudo
```
Add:
```
Defaults        log_input,log_output
Defaults        iolog_dir=/var/log/sudo
Defaults        logfile="/var/log/sudo/sudo.log"
```
Validate with `visudo -c`.

### 6. AppArmor
```bash
apt install apparmor apparmor-utils
aa-status
```
Confirm it's enabled and enforcing profiles.

### 7. Monitoring script
Write `monitoring.sh` to gather: architecture, physical/virtual CPU count, RAM usage, disk usage, CPU load, last boot, LVM use, active TCP connections, logged-in users, IP/MAC, sudo command count — broadcast with `wall`.

```bash
crontab -e -u root
```
Add:
```
*/10 * * * * /path/to/monitoring.sh
```
Check it's registered: `crontab -l -u root`.

### 8. Bonus (WordPress + OpenLiteSpeed + MariaDB)
```bash
wget -O - https://repo.litespeed.sh | sudo bash
apt install openlitespeed lsphp php-mysqli mariadb-server
mysql_secure_installation
```
Create a database and dedicated DB user for WordPress, download and extract WordPress into the web root, configure `wp-config.php` with the DB credentials, set correct ownership/permissions, then complete setup through the browser install wizard.

### Networking reminder (host ⇄ VM)
- **NAT mode** (VirtualBox default): the VM's internal IP (e.g. `10.0.2.x`) is not directly reachable from the host. Set up port forwarding: `VBoxManage controlvm "vm-name" natpf1 "ssh,tcp,,2222,,4242"`, then connect from the host with `ssh username@localhost -p 2222`.
- **Bridged mode**: the VM gets an IP on the same LAN as the host (e.g. `192.168.x.x`), reachable directly — `hostname -I` inside the VM gives the address to SSH into from the host (or from WSL, if the host's network is reachable from there).

---

## Troubleshooting notes (from real issues encountered)

- **`sh` vs `bash`**: if a script's shebang is `#!/bin/bash`, run it with `bash script.sh` or `./script.sh` after `chmod +x`, not `sh script.sh` — `sh` is often `dash` on Debian and behaves differently.
- **`wall` produces no output**: often caused by `mesg n` on the receiving terminal (`mesg y` to fix), the terminal's tty lacking group-write permission, or (rarer) SSH sessions having their tty permissions reset by a PAM session module on login — `/etc/login.defs`'s `TTYPERM` explicitly does **not** apply to remote/SSH logins, only local console logins via `login(1)`. Workaround when `mesg` itself is missing from the system: `echo 'chmod g+w $(tty) 2>/dev/null' >> ~/.bashrc`.
- **`mesg: command not found`**: on Debian trixie, `mesg` was found to be missing even after reinstalling `util-linux`, `bsdutils`, and `bsdextrautils` — none of which contained it on this system; a direct `chmod g+w $(tty)` was used as a working substitute.
- **Broken `sudoers` file**: a typo (e.g. `Dafaults` instead of `Defaults`) in a file under `/etc/sudoers.d/` breaks `sudo` entirely. Always edit with `visudo -f /path/to/file`, which validates syntax before saving, to avoid a total lockout.
- **`&&` chaining hides failures**: `sudo apt update && sudo apt install -y curl` skips the install entirely if `apt update` exits non-zero (e.g. due to an unrelated repo warning) — run the two commands separately when one might legitimately "fail" without blocking the other.
- **GPG/repo signature errors**: "not signed" repo errors are commonly caused by a missing key import (often because `curl`/`gnupg` weren't installed yet) or a mis-written `sources.list.d` entry (verify the correct key URL and component names by checking the vendor's actual repo, not guessing filenames).
- **`git status` showing deleted tracked files**: stage deletions in bulk with `git add -u`, then commit; add `*.o` and build directories to `.gitignore` going forward, and `git rm -r --cached <dir>` to untrack anything still tracked.

---

## Resources

### Classic references
- [42 Born2beroot subject PDF](https://cdn.intra.42.fr/pdf/pdf/) — official project subject (check your campus intranet for the current version).
- [Debian Administrator's Handbook](https://debian-handbook.info/) — free, comprehensive Debian reference.
- [Debian Wiki: LVM](https://wiki.debian.org/LVM)
- [Arch Wiki: LVM](https://wiki.archlinux.org/title/LVM) — distro-agnostic, very thorough LVM reference.
- [man pages](https://man7.org/): `man sudoers`, `man sshd_config`, `man crontab`, `man chage`, `man ufw`, `man apparmor`
- [AppArmor documentation](https://gitlab.com/apparmor/apparmor/-/wikis/Documentation)
- [SELinux Project Wiki](https://selinuxproject.org/page/Main_Page)
- [UFW documentation (Ubuntu/Debian wiki)](https://help.ubuntu.com/community/UFW)
- [firewalld documentation](https://firewalld.org/documentation/)
- [WordPress Codex — Installing WordPress](https://wordpress.org/documentation/article/how-to-install-wordpress/)
- [OpenLiteSpeed documentation](https://openlitespeed.org/kb/)
- [MariaDB documentation](https://mariadb.com/kb/en/documentation/)
- [PAM documentation (Linux-PAM)](http://www.linux-pam.org/Linux-PAM-html/)

### AI usage disclosure
Claude (Anthropic) was used throughout this project as a learning and debugging aid, in the following ways:

- **Conceptual explanations**: understanding virtualization (VM vs container, hypervisor types), LVM's PV/VG/LV chain, MAC vs DAC, AppArmor vs SELinux, PAM's role, apt vs aptitude vs dpkg, and UFW/nftables/netfilter — used to build the "Comparisons" and "Design Choices" sections of this README.
- **Live debugging assistance**: diagnosing why `monitoring.sh` produced no output (`wall`/`mesg` permission chain), a broken `/etc/sudoers.d/` file from a typo, missing `curl`/`gnupg`/`mesg` binaries, a malformed `sources.list.d` entry for the OpenLiteSpeed repository, and a corrupted `mysql_secure_installation` command chain.
- **Command reference and syntax help**: correct usage of `chage`, `crontab`, `hostnamectl`, `getent`, `git add -u`, and shell variable/quoting mistakes (e.g. `ARG="9 8" ./push_swap $ARG`).
- **Quizzes for self-testing**: interactive multiple-choice quizzes generated on each topic above, used to check understanding before the project defense.
- **This README**: drafted by AI based on the actual questions asked and troubleshooting performed over the course of this project, then intended for review/editing by the student before submission.

No AI was used to generate the `monitoring.sh` script's actual command logic beyond the debugging described above — the script's core logic and awk/shell arithmetic were written independently.
