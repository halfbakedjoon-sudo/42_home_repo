#!/usr/bin/env python3


def secure_archive(filename: str, action: str, write: str = ""
                   ) -> tuple[bool, str]:
    try:
        if action == "read":
            with open(filename, "r", encoding="utf-8") as fd:
                content: str = fd.read()
                condition = True, content
        elif action == "write":
            if write:
                with open(filename, "w", encoding="utf-8") as fd:
                    fd.write(write)
                    condition = True, write
            else:
                raise OSError("Please put in message to write")
        else:
            condition = False, f"Unknown action: {action}"
    except OSError as e:
        error_condition: tuple[bool, str] = False, str(e)
        return (error_condition)
    return (condition)


def check_status(success: bool, message: str) -> None:
    if success:
        safe_message: str = message.replace("\n", "\\n")
        print(f"True, '{safe_message}'\n")
    else:
        print(f"False, '{message}'\n")


def ft_vault_security() -> None:
    print("=== Cyber Archives Security ===")

    print("\nUsing 'secure_archive' to read from a nonexistent file:")
    success, message = secure_archive("/not/existing/file", "read")
    check_status(success, message)

    print("Using 'secure_archive' to read from an inaccessible file:")
    success, message = secure_archive("/etc/master.passwd", "read")
    check_status(success, message)

    print("Using 'secure_archive' to read from a regular file:")
    success, message = secure_archive("ancient_fragment.txt", "read")
    check_status(success, message)

    print("Using 'secure_archive' to write to a regular file:")
    success, message = secure_archive("a.txt", "write", "how are you")
    check_status(success, message)

    print("Using 'secure_archive' to write to a regular file but no message:")
    success, message = secure_archive("a.txt", "write")
    check_status(success, message)


if __name__ == "__main__":
    ft_vault_security()
