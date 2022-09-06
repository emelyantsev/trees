Here are my implementations of some tree-like data structures:

- Binary search tree
- AVL tree
- AVL tree with sum

I also prepared some tests and [benchmark](https://github.com/emelyantsev/trees/blob/main/Tests/benchmark_01.ipynb).
Benchmark shows that avl performs quite well comparatively to std::set.

Here are the [solution](https://github.com/emelyantsev/trees/tree/main/StepikSolution) for challenging Stepik [problem](https://stepik.org/lesson/45970/step/4?unit=24123)

Steps to improve:
- use inheritance
- use templates
- add more handy member functions
- use less recursion
- add another types of trees
- add linux build scripts

## Binary search tree
![Insertion to BST](https://github.com/emelyantsev/trees/blob/main/Images/bst.png)

## AVL tree
![Insertion to AVL](https://github.com/emelyantsev/trees/blob/main/Images/avl.png)

## Rotations in AVL tree (left/right)
![Simple rotations](https://github.com/emelyantsev/trees/blob/main/Images/right.png)

## Rotations in AVL tree (leftRight/rightLeft)
![Complicated rotations](https://github.com/emelyantsev/trees/blob/main/Images/leftRight.png)