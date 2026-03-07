Here is the PDF contents:

# Ain Shams University
## Faculty of Engineering
### Computer Engineering and Software Systems Program
### CSE245: Design and Analysis of Algorithms — Spring 2026

---

# PROJECT REQUIREMENTS

This project is a group project with each group has 10 up to 12 students. Each team must do the following Tasks:

---

## Task 1

Devise an algorithm for the following task: given a **2n × 2n** (n > 1) board with one missing square, tile it with right trominoes of only three colors so that no pair of trominoes that share an edge have the same color. Recall that the right tromino is an L-shaped tile formed by three adjacent squares.

Use **Divide and Conquer** and **Brute Force** technique to solve this problem.

---

## Task 2

Is it possible for a chess knight to visit all the cells of an **8 × 8** chessboard exactly once, ending at a cell one knight's move away from the starting cell? (Such a tour is called closed or re-entrant. Note that a cell is considered visited only when the knight lands on it, not just passes over it on its move.)

What if the chessboard is **n × n**? Is all n where n > 8 possible for a chess knight to visit all the cells? If not, what are the cases?

Design a **greedy algorithm** to find the minimum number of moves the chess knight needs. And study the different cases of n.

---

## Task 3

There are eight disks of different sizes and four pegs. Initially, all the disks are on the first peg in order of size, the largest on the bottom and the smallest on the top.

Use **divide and conquer** method to transfer all the disks to another peg by a sequence of moves. Only one disk can be moved at a time, and it is forbidden to place a larger disk on top of a smaller one.

Does the **Dynamic Programming** algorithm solve the puzzle in **33 moves**? If not, then design an algorithm that solves the puzzle in 33 moves.

Then design a **Dynamic Programming** algorithm to solve any number of disks of different sizes and four pegs puzzle.

---

## Task 4

There are six knights on a **3 × 4** chessboard: the three white knights are at the bottom row, and the three black knights are at the top row.

```
[ B ][ B ][ B ]          [ W ][ W ][ W ]
[   ][   ][   ]    →     [   ][   ][   ]
[   ][   ][   ]          [   ][   ][   ]
[ W ][ W ][ W ]          [ B ][ B ][ B ]
```

Design an **iterative improvement** algorithm to exchange the knights to get the position shown on the right of the figure in the minimum number of knight moves, not allowing more than one knight on a square at any time.

---

## Task 5

A computer game has a shooter and a moving target. The shooter can hit any of **n > 1** hiding spots located along a straight line in which the target can hide. The shooter can never see the target; all he knows is that the target moves to an adjacent hiding spot between every two consecutive shots.

Design a **Divide and Conquer** algorithm that guarantees hitting the target. (**DON'T USE DECREASE AND CONQUER**)

---

## Task 6

Given an **n × n** point lattice (intersection points of n consecutive horizontal and n consecutive vertical lines on common graph paper), where **n > 2**, cross out all the points by **2n − 2** straight lines without lifting your pen from the paper. You may cross the same point more than once, but you cannot redraw any portion of the same line.

> A solution for n = 4 has seven lines instead of the six required by the puzzle.

Design a **Dynamic Programming** algorithm to solve this problem.

---

## Task 7

A company must schedule jobs on one machine.  
Each job has processing time **t[i]** and penalty **p[i]** if finished after deadline **d[i]**.  
Minimize total penalty.

Solve this problem using **Dynamic Programming**, **Brute Force**, and **Divide and Conquer**.

---

## Task 8

Given a weighted graph, find an approximate minimum cut using local improvement.

Solve this problem using **Iterative Improvement** and **Brute Force**.

---

## Task 9

Cluster points into **k clusters**.

Use **Iterative Improvement**, **Divide and Conquer**, and **Brute Force** to solve this problem.

---

## Task 10

There is a line of **n coins** on the table; some of them are heads up and the rest are tails up, in no particular order. The object of the puzzle is to remove all the coins by a sequence of moves. On each move, one can remove any head-up coin, after which its neighboring coin or coins, if any, must be turned over. Coins are considered "neighbors" if they are next to each other in the original line; if there is a gap between two coins after some moves, the coins are no longer considered "neighbors."

**Example** (the head-up coin being removed is shown in **bold**):

```
T  H  H  T  H  H  H
T  H  H  H  _  T  H
H  _  T  H  _  T  H
_  _  T  H  _  T  H
_  _  H  _  _  T  H
_  _  _  _  _  T  H
_  _  _  _  _  H  _
_  _  _  _  _  _  _
```

---

## Report Requirements

The report **MUST** contain each of the following:

1. **Cover Page** — must include the group members' names, college name, program name, course code, course title, and any other relevant information.
2. Present all underlying **assumptions** in a clear and detailed manner.
3. Provide a comprehensive **description of the problem** being addressed.
4. Deliver a detailed **explanation of the solution**, including the pseudocode, implementation code, and a step-by-step description of the methodology.
5. Conduct a thorough analysis of the algorithm's **time and space complexity**.
6. Provide a **comparative evaluation** of the techniques used in the solution.
7. Offer a **complete analysis** for each problem, including a discussion of alternative approaches and whether more efficient techniques exist beyond the implemented one.
8. Present **sample outputs** for various cases, accompanied by clear and appropriate explanations.
9. **Summarize** the key findings and insights derived from the work.
10. **List all references** and ensure they are properly cited within the document.
11. Include any other relevant sections deemed necessary to enhance the clarity and completeness of the report.

---

## Project Deliverables

All deliverables must be submitted on the LMS. No deliverable will be accepted by any other means. The following are required to be delivered by the due date:

1. **Project code** using any of the following programming languages: C++, C#, Java. Must be submitted as a `.zip` / `.rar` archive.
2. **A presentation** (in `.pptx` format) of the different phases of the project. Each group will do the presentation and project demo via Microsoft Teams after submitting the project.
3. **Project document** (in `.docx` format) that contains at least the above-mentioned sections.

---

## Formatting Instructions

The following instructions **MUST** be taken into consideration:

- Use **consistent document format** (font sizes, titles, subtitles, captions, paragraph formatting, etc.).
  - Main title: **14pt bold Calibri**
  - Subtitles: **12pt bold Calibri**
  - Main text: **12pt regular Calibri**
  - Captions: **10pt regular Calibri**
  - Spacing: 12pt before and 6pt after each paragraph; 1.5 line spacing recommended.
  - Paragraphs must be **justified from both sides**.
- **Figures and tables** must be centered on the page and numbered separately.
  - Each figure must have a caption **below** it.
  - Each table must have a title **above** it.
- **Pages must be numbered** consistently, except for the cover page.
- A **Table of Contents** must be included showing titles, subtitles, and corresponding page numbers.
- **List of Figures** and **List of Tables** must be included if applicable.
- All reports must be written in **English**; always avoid typos and grammatical errors.
- All submitted files will undergo **plagiarism check**.
- All project deliverables must be uploaded to the LMS. No hardcopy is accepted. Do not send deliverables by email.