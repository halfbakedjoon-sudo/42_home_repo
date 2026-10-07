"""Dou Shou Qi (Jungle / Animal Chess) - two players, one terminal."""
from __future__ import annotations

from dataclasses import dataclass
from typing import Optional

COLS, ROWS = 7, 9
Pos = tuple[int, int]  # (col, row), both 0-indexed; row 0 is Player 1's back row

RANKS: dict[str, int] = {"R": 1, "C": 2, "D": 3, "W": 4, "P": 5, "T": 6, "L": 7, "E": 8}
NAMES: dict[str, str] = {
    "R": "Rat", "C": "Cat", "D": "Dog", "W": "Wolf",
    "P": "Leopard", "T": "Tiger", "L": "Lion", "E": "Elephant",
}

WATER: set[Pos] = {(c, r) for c in (1, 2, 4, 5) for r in (3, 4, 5)}
DENS: dict[int, Pos] = {0: (3, 0), 1: (3, 8)}
TRAPS: dict[int, set[Pos]] = {
    0: {(2, 0), (4, 0), (3, 1)},
    1: {(2, 8), (4, 8), (3, 7)},
}
DIRECTIONS: list[Pos] = [(1, 0), (-1, 0), (0, 1), (0, -1)]


@dataclass(frozen=True)
class Piece:
    kind: str   # one of RANKS' keys
    owner: int  # 0 = Player 1 (bottom), 1 = Player 2 (top)

    @property
    def rank(self) -> int:
        return RANKS[self.kind]

    @property
    def symbol(self) -> str:
        return self.kind if self.owner == 0 else self.kind.lower()


def starting_board() -> dict[Pos, Piece]:
    """Player 1's layout; Player 2's is the same rotated 180 degrees."""
    layout: dict[Pos, str] = {
        (0, 0): "L", (6, 0): "T",
        (1, 1): "D", (5, 1): "C",
        (0, 2): "R", (2, 2): "P", (4, 2): "W", (6, 2): "E",
    }
    board: dict[Pos, Piece] = {}
    for (c, r), kind in layout.items():
        board[(c, r)] = Piece(kind, 0)
        board[(COLS - 1 - c, ROWS - 1 - r)] = Piece(kind, 1)
    return board


class Game:
    def __init__(self) -> None:
        self.board: dict[Pos, Piece] = starting_board()

    # ---------- rules ----------

    def can_capture(self, src: Pos, dst: Pos) -> bool:
        a = self.board[src]
        t = self.board[dst]
        if a.owner == t.owner:
            return False
        # Rat in water and anything on land can't hit each other.
        if (src in WATER) != (dst in WATER):
            return False
        # A piece standing in an enemy trap has rank 0: anything can take it.
        if dst in TRAPS[a.owner]:
            return True
        # A trapped attacker has rank 0 and can't capture a normal piece.
        if src in TRAPS[t.owner]:
            return False
        if a.kind == "R" and t.kind == "E":
            return True
        if a.kind == "E" and t.kind == "R":
            return False
        return a.rank >= t.rank

    def legal_moves(self, src: Pos) -> list[Pos]:
        piece = self.board.get(src)
        if piece is None:
            return []
        moves: list[Pos] = []
        c, r = src
        for dc, dr in DIRECTIONS:
            nxt = (c + dc, r + dr)
            if not (0 <= nxt[0] < COLS and 0 <= nxt[1] < ROWS):
                continue
            dest: Optional[Pos] = nxt
            if nxt in WATER:
                if piece.kind == "R":
                    dest = nxt
                elif piece.kind in ("L", "T"):
                    dest = self._jump(nxt, dc, dr)
                else:
                    dest = None
            if dest is None or dest == DENS[piece.owner]:
                continue
            if dest in self.board and not self.can_capture(src, dest):
                continue
            moves.append(dest)
        return moves

    def _jump(self, first_water: Pos, dc: int, dr: int) -> Optional[Pos]:
        """Lion/Tiger leap over the river; blocked if any rat sits in the way."""
        pos = first_water
        while pos in WATER:
            if pos in self.board:
                return None
            pos = (pos[0] + dc, pos[1] + dr)
        return pos

    def has_moves(self, player: int) -> bool:
        return any(
            self.legal_moves(pos)
            for pos, p in self.board.items()
            if p.owner == player
        )

    def move(self, src: Pos, dst: Pos) -> bool:
        """Apply a move. Returns True if the mover has just won."""
        piece = self.board.pop(src)
        self.board[dst] = piece
        if dst == DENS[1 - piece.owner]:
            return True
        return not any(p.owner != piece.owner for p in self.board.values())

    # ---------- display ----------

    def show(self) -> None:
        print("\n     a b c d e f g")
        for r in range(ROWS - 1, -1, -1):
            cells = []
            for c in range(COLS):
                pos = (c, r)
                if pos in self.board:
                    cells.append(self.board[pos].symbol)
                elif pos in WATER:
                    cells.append("~")
                elif pos in TRAPS[0] or pos in TRAPS[1]:
                    cells.append("^")
                elif pos in DENS.values():
                    cells.append("#")
                else:
                    cells.append(".")
            print(f"  {r + 1}  " + " ".join(cells) + f"  {r + 1}")
        print("     a b c d e f g")


def parse_square(text: str) -> Optional[Pos]:
    if len(text) != 2 or not text[1].isdigit():
        return None
    col = ord(text[0]) - ord("a")
    row = int(text[1]) - 1
    if 0 <= col < COLS and 0 <= row < ROWS:
        return (col, row)
    return None


def square_name(pos: Pos) -> str:
    return f"{chr(ord('a') + pos[0])}{pos[1] + 1}"


HELP = """
Commands:
  e3 e4     move the piece on e3 to e4
  e3        show the legal moves for the piece on e3
  help      show this message
  quit      leave the game
Pieces (strongest to weakest): E L T P W D C R
  Elephant, Lion, Tiger, Leopard, Wolf, Dog, Cat, Rat
  UPPERCASE = Player 1 (bottom), lowercase = Player 2 (top)
Board: ~ water   ^ trap   # den
"""


def main() -> None:
    game = Game()
    turn = 0
    players = ["Player 1 (UPPERCASE)", "Player 2 (lowercase)"]
    print("Dou Shou Qi - type 'help' for commands.")

    while True:
        game.show()
        if not game.has_moves(turn):
            print(f"\n{players[turn]} has no legal moves. {players[1 - turn]} wins!")
            return

        raw = input(f"\n{players[turn]} > ").strip().lower()
        if raw in ("quit", "exit", "q"):
            return
        if raw == "help":
            print(HELP)
            continue

        squares = raw.replace(",", " ").split()
        if len(squares) == 1 and len(squares[0]) == 4:  # "e3e4"
            squares = [squares[0][:2], squares[0][2:]]

        parsed = [parse_square(s) for s in squares]
        if not parsed or len(parsed) > 2 or any(p is None for p in parsed):
            print("Couldn't read that. Try something like 'e3 e4' or 'help'.")
            continue

        src = parsed[0]
        assert src is not None
        piece = game.board.get(src)
        if piece is None or piece.owner != turn:
            print("You don't have a piece there.")
            continue

        options = game.legal_moves(src)
        if len(parsed) == 1:
            listing = ", ".join(square_name(p) for p in options) or "none"
            print(f"{NAMES[piece.kind]} on {squares[0]} can go to: {listing}")
            continue

        dst = parsed[1]
        assert dst is not None
        if dst not in options:
            print("Illegal move.")
            continue

        target = game.board.get(dst)
        won = game.move(src, dst)
        if target is not None:
            print(f"{NAMES[piece.kind]} captures {NAMES[target.kind]}!")
        if won:
            game.show()
            print(f"\n{players[turn]} wins!")
            return
        turn = 1 - turn


if __name__ == "__main__":
    main()
