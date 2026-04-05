# ♟️ Twixt Terminal Engine v2.0

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/4/4e/Twixt_board_geometry.svg" alt="Twixt Geometry" width="400">
</p>

A high-performance, polished terminal-based implementation of the classic strategy board game **Twixt**, written in clean, modular C.

---

## ✨ Features
- **Polished CLI Interface**: Rich ANSI color rendering and character output structure for a premium terminal experience.
- **Robust Rule Enforcement**: Precise knight-move validation using squared Euclidean distance ($d^2 = 5$) and cross-link intersection blocking.
- **Efficient Win Detection**: Optimized Breadth-First Search (BFS) graph traversal to detect winning paths across the board grid.
- **Modular Codebase**: Decoupled engine logic, command-line parsing, and ANSI rendering to ensure scalability and straightforward maintenance.
- **Safe Command Parsing**: Hardened input handlers with verbose error messages and helpful instruction support.

---

## 🛠 Project Structure
| File | Description |
| :--- | :--- |
| **`main.c`** | Entry point executing the high-level game loop state machine. |
| **`engine.c`** | Core engine implementation. Handles coordinate validation, matrix operations, distance calculations, vector intersections via determinants, and bounded BFS. |
| **`cmd.c`** | Lexical parsing of user string commands into internal game actions. |
| **`render.c`** | Terminal rendering engine utilizing ANSI escape sequences to draw the HUD and the DIMxDIM grid. |
| **`proto.h`** | Shared data structures (e.g. `TwixtBoard`, `Link`, `Point`) and system-wide function prototypes. |
| **`Makefile`** | GNU Make automated build definitions. |

---

## 🔬 Technical Implementation Details

### **Link Collision & Intersection Math**
The engine ensures links never cross each other by modelling points as vectors in a 2D plane. It checks intersection between two segments `(A, B)` and `(C, D)` using line-intersection determinants:
`det = (y4-y3)*(x2-x1) - (x4-x3)*(y2-y1)`
If segments intersect strictly inside bounds (`ua, ub ∈ (0,1)`), the linkage is rejected.

### **Win Detection (BFS)**
Victory is verified at the end of each turn via a Breadth-First Search (BFS) queue. For the Red player, the engine enqueues all pegs placed at column `0`. It uncovers the linked graph until it hits a node located at column `DIM-1`, achieving $O(V + E)$ efficiency.

### **Knight's Move Validation**
A valid Twixt link must form a geometric knight's move in chess. Instead of complex branches, the engine simply calculates coordinate delta squares:
`dist_sq = (p1.r - p2.r)^2 + (p1.c - p2.c)^2`
The distance must evaluate precisely to `5` to constitute a valid move.

---

## 🚀 Getting Started

### Prerequisites
- A standard C compiler (`gcc` or `clang`).
- GNU `make` automation utility.
- True-Color ANSI terminal emulation.

### Build & Run
```bash
# Clone the repository and traverse into it
cd twixt

# Compile the application via Makefile
make

# Execute the local binary
./twixt_engine
```

**Clean build cache:**
```bash
make clean
```

---

## 🕹 How to Play

### Rules
- **Objective**: Connect your two home boundaries with a continuous path of linked pegs.
  - 🔴 **RED**: Connects **Left** to **Right**.
  - ⚫ **BLACK**: Connects **Top** to **Bottom**.
- **Turn Flow**:
  1. Place **exactly one** peg on an available coordinate.
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
- **`●`** : Your placed pegs (colored Red or Cyan depending on your team).
- **`·`** : Free holes available for placement.
- **`-` / `|`** : Boundary indicators denoting Red and Black home bases.

---

## 🔒 License

***Copyright © 2026. All rights reserved.***

This source code is proprietary and confidential. It may not be copied, reproduced, modified, republished, uploaded, posted, transmitted, or distributed in any way without explicit written permission from the author. Unauthorized use, distribution, or reproduction is strictly prohibited. 

---
*Created with ❤️ for strategy game enthusiasts.*
