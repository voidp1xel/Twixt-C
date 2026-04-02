# Twixt Terminal Engine v2.0 🎮

A high-performance, polished terminal-based implementation of the classic strategy board game **Twixt**, written in clean, modular C.

![Game Preview](https://upload.wikimedia.org/wikipedia/commons/4/4e/Twixt_board_geometry.svg)
*(Sample Twixt Geometry)*

---

## ✨ Features
- **Polished CLI Interface**: Uses ANSI colors and high-quality characters for a premium terminal experience.
- **Robust Rule Enforcement**: Handles knight-move validation, link intersections, and boundary constraints.
- **Efficient Win Detection**: Implements a Breadth-First Search (BFS) to detect winning paths across the board.
- **Modular Codebase**: Separated engine logic, command parsing, and rendering for easy maintenance.
- **Safe Command Parsing**: Robust input handling with error messages and instruction support.

---

## 🛠 Project Structure
| File | Description |
| :--- | :--- |
| `main.c` | Entry point and high-level game loop. |
| `engine.c` | Core game logic (placement, linking, win-checking). |
| `cmd.c` | User command parser and turn management. |
| `render.c` | Terminal rendering and ANSI HUD. |
| `proto.h` | Shared data structures and function prototypes. |
| `Makefile` | Automated build system. |

---

## 🚀 Getting Started

### Prerequisites
- A C compiler (GCC or Clang).
- `make` utility.
- A terminal with ANSI color support (standard on macOS/Linux).

### Build & Run
1. **Clone and enter the directory**:
   ```bash
   cd twixt
   ```
2. **Build the project**:
   ```bash
   make
   ```
3. **Execute the game**:
   ```bash
   ./twixt_engine
   ```

To clean build files:
```bash
make clean
```

---

## 🕹 How to Play

### Rules
- **Objective**: Connect your two home boundaries with a continuous path of linked pegs.
  - **RED**: Connects **Left** to **Right**.
  - **BLACK**: Connects **Top** to **Bottom**.
- **Turn Flow**:
  1. Place **exactly one** peg on a valid hole.
  2. Create or remove as many links as you want between your own pegs.
  3. Type `done` (or `d`) to end your turn.
- **Linking**: Links must be a **knight's move** away (2 holes in one direction, 1 in another). Links cannot cross each other.

### Command Reference
| Command | Usage | Description |
| :--- | :--- | :--- |
| **Place** | `p r c` | Place a peg at Row `r`, Column `c`. |
| **Link** | `l r1 c1 r2 c2` | Create a link between two of your pegs. |
| **Unlink** | `u r1 c1 r2 c2` | Remove an existing link. |
| **Done** | `d` | End your turn. |
| **Show** | `s` | Refresh the board view. |
| **Help** | `h` | View command help. |
| **Quit** | `q` | Exit the game. |

---

## 🎨 Interface Guide
- `●` : Your pegs (Red or Cyan).
- `·` : Available holes.
- `-` / `|` : Boundary lines for Red and Black respectively.

---

## 📝 License
This project is open-source and available under the MIT License.

---
*Created with ❤️ for strategy game enthusiasts.*
