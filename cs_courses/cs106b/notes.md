

18wi lecture 16: binary trees

  tree: a directed, acyclic structure of linked nodes
  acyclic: no path wraps back around to the same node twice

  recursive definition: a tree is either:
  - empty (nullptr), or
  - a root node that contains:
    - data
    - a left subtree, and
    - a right subtree

Terminology
* node: an object conntaining a data value and left/right children
  - root: topmost node of a tree
  - leaf: a node that has no children
  - branch: any internal node; neither root nor a leaf
  - parent: a node that refers to this one
  - child: a node that this node refers to
  - sibling: a node with a common parent

* subtree: the smaller tree of nodes on the left or right of the current node
* height: length of the longest path from the root to any node
* level/depth: length of the path from a root to a given node


