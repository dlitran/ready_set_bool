# Ready Set Boole

## 📌 About The Project
`ready_set_boole` is a 42 school project designed to introduce the foundational concepts of computer-related mathematics. It focuses on Boolean Algebra, Set Theory, Logic, and Space-Filling Curves. 

Through a series of algorithmic exercises, this project explores how computers handle arithmetic operations under the hood using purely bitwise logic. It then progresses into parsing and evaluating propositional formulas, generating truth tables, and converting mathematical formulas into their Negation Normal Form (NNF) and Conjunctive Normal Form (CNF).

## 🚀 Exercises Overview

The project is structured sequentially, building upon previous logic:

* **ex00 - Adder**: Implement an adder for natural numbers using *only* bitwise operators (`&`, `|`, `^`, `<<`, `>>`).
* **ex01 - Multiplier**: Implement a multiplier for natural numbers using purely bitwise logic.
* **ex02 - Gray Code**: Create a function that takes an integer and returns its equivalent in Gray Code.
* **ex03 - Boolean Evaluation**: Evaluate a propositional formula provided in Reverse Polish Notation (RPN).
* **ex04 - Truth Table**: Generate and print the complete truth table for a given propositional formula.
* **ex05 - Negation Normal Form (NNF)**: Convert a propositional formula into NNF, ensuring negations are only applied directly to variables.
* **ex06 - Conjunctive Normal Form (CNF)**: Convert an NNF formula into CNF using distributive laws.
* **ex07 - Powerset**: Given a set of integers, calculate and return its powerset.
* **ex08 - Set Evaluation**: Evaluate a propositional formula on a list of mathematical sets.
* **ex09 - Set to Line**: Encode a pair of 2D coordinates into a unique value on a line (Space-Filling Curve).
* **ex10 - Line to Set**: Decode a one-dimensional value back into a 2D spatial coordinate.

## 🛠️ Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/dlitran/ready_set_boole.git
   cd ready_set_boole
   ```
2. Compile the exercises:
   ```bash
   make
   ```
3. Run the executable for a specific exercise to view the test cases:
   ```bash
   ./readySetBoole
   ```

## 📚 Concepts Learned
* **Bitwise Operations**: Understanding how `AND`, `OR`, `XOR`, and bit shifting can perfectly replicate arithmetic without using `+` or `*`.
* **Reverse Polish Notation (RPN)**: Parsing and evaluating formulas efficiently using a Stack data structure.
* **Abstract Syntax Trees (AST)**: Representing logical formulas as trees to easily manipulate and convert them (crucial for CNF/NNF conversions).
* **Set Theory**: Managing operations on mathematical sets and generating combinatorial combinations like powersets.
* **Space-Filling Curves**: Learning the mathematical foundations of mapping multi-dimensional data into a one-dimensional space.

## 👤 Author
* **dlitran** - [GitHub Profile](https://github.com/dlitran)
