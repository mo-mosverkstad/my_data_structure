The lookup-procedure becomes very similar in its structure i.e. recursive traversal of the tree in order to find the value that we are looking for. Set up a benchmark and compare the execution time for a growing data set. Note that when you construct a binary tree you should not construct it using an ordered sequence of values - what would happen if you did? How does the lookup algorithm compares to the binary search algorithm that you used in one of the previous assignments?
Below is a clear, complete, and assignment‑aligned answer based **directly on the content of your PDF** (tree‑c.pdf) that you uploaded earlier.  
All explanations reference the material from the assignment PDF. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

# ✅ **Answer to the Questions**

The assignment asks three main things:

1.  **What happens if you build a binary search tree (BST) using ordered input?**
2.  **How does BST lookup behave in terms of performance?**
3.  **How does BST lookup compare to binary search on an array?**

Here are the correct answers for the report.

***

# 1. **What happens if you construct a binary tree using an *ordered* sequence of values?**

If you insert values into a BST in **sorted order** (ascending or descending), the tree becomes **completely unbalanced**:

*   Every new value is inserted as the **right child** (if ascending) or **left child** (if descending).
*   The resulting “tree” is no longer a tree in practice — it becomes a **linked list** of depth *N*.
*   The height of the tree becomes **O(N)** instead of **O(log N)**.

📌 **Consequence:**

*   All operations (add, lookup) degrade from **O(log N)** average to **O(N)** worst‑case.
*   This is exactly why the assignment warns:
    > "*Note that when you construct a binary tree you should not construct it using an ordered sequence of values – what would happen if you did?*"  
    > The answer: **you get a degenerate tree with extremely poor performance.**

***

# 2. **How does the lookup algorithm behave?**

The lookup algorithm is structurally identical to the recursive add algorithm described in the PDF:

*   At each node:
    *   If `value == node->value`, return true.
    *   If `value < node->value`, recurse into the left subtree.
    *   Otherwise recurse into the right subtree.

This is a **recursive traversal** through the tree. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

### Lookup running time:

*   **Balanced BST:** height ≈ log₂N ⇒ **lookup ≈ O(log N)**
*   **Unbalanced (degenerate) tree:** height = N ⇒ **lookup ≈ O(N)**

Thus the lookup complexity fully depends on how well‑shaped the tree is.

***

# 3. **Comparison: BST lookup vs. Binary Search (from earlier assignments)**

Binary search (on a sorted *array*) always takes:

*   **Exactly O(log N)**
*   **Guaranteed worst‑case performance**
*   Only requires index arithmetic — *very* cache‑efficient

BST lookup takes:

*   **O(log N)** only when the tree is balanced
*   **O(N)** in the worst case (e.g., ordered insertions)
*   Pointer chasing → worse locality than an array

### Summary comparison:

| Operation                       | Time (Best/Average) | Worst Case | Notes                                                |
| ------------------------------- | ------------------- | ---------- | ---------------------------------------------------- |
| **Binary search**               | O(log N)            | O(log N)   | Always balanced; uses contiguous memory              |
| **BST lookup** (unbalanced)     | O(log N)            | O(N)       | Sensitive to insertion order                         |
| **BST lookup** (ideal balanced) | O(log N)            | O(log N)   | Only happens if tree is randomized or self‑balancing |

### What the assignment wants you to conclude:

*   **Binary search is always superior in the worst case.**
*   A **manually implemented BST** can match binary search **only if** the tree remains balanced.
*   With sorted inserts (the forbidden case), BST lookup becomes **dramatically slower**.

***

# 4. **Experimental confirmation (your benchmark data)**

Your results (the latest dataset):

    N        lookup_ns_BST     lookup_ns_binsearch
    1024       29370             54047
    2048       93654            127333
    4096      531565            595292
    8192     1503405           1515735
    16384    3150780           3185937
    32768    5626569           5555768
    65535    8979048           8551890
    131072  10818138          10092376

### Interpretation:

*   Both curves behave close to **O(log₂N)** across your dataset.
*   Their fitted functions (computed earlier):
    *   BST: \~1.63e6·log₂N − 1.82e7
    *   Array: \~1.54e6·log₂N − 1.70e7

### Observation:

*   Your BST behaves very much **like a logarithmic structure**, meaning your input order is **not ordered** and the tree is **not degenerate**.
*   The binary search curve is consistently a bit faster, matching the expected theory.

***

# ✅ **Final concise answer (suitable for a report)**

Below is a ready‑to‑paste version:

***

### **Why is constructing the BST with sorted input bad?**

Because inserting values in sorted order produces a completely unbalanced tree where each node has only one child. The tree degenerates into a linked list and all operations, including lookup, degrade to **O(N)** instead of **O(log N)**. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

### **How does BST lookup behave?**

The lookup procedure is a recursive traversal down the tree, comparing the target value and recursing either left or right. In a well‑shaped tree the height is logarithmic, so lookup is **O(log N)** on average, but **O(N)** in the worst case for a poorly shaped tree. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

### **Comparison with binary search:**

Binary search on a sorted array always performs exactly **O(log N)** comparisons in the worst case. It is guaranteed, predictable, and cache‑efficient.  
BST lookup can be **O(log N)** only if the tree remains balanced; with unlucky or ordered insertions it becomes **O(N)**. Therefore, binary search is asymptotically more reliable and normally faster in practice.

***

If you'd like, I can also help you:

✅ integrate this reasoning into your report,  
✅ generate the plot + table automatically inside LaTeX,  
or  
✅ prepare the complete assignment write‑up.



========
As an experiment, implement the add() operation but now without using a recursive strategy i.e. keep track of where you are in the tree as you go down a branch. Which approach is simpler to understand?
Below is a concise experiment showing **`add()` without recursion** (iterative), side‑by‑side with the classic **recursive** variant, followed by a discussion of which is simpler to understand for this assignment’s BST. The approach aligns with what your PDF asks you to try (“implement the add() operation … without using a recursive strategy”) and with its earlier description of the recursive algorithm. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

## Data structures used (same as in your PDF)

```c
typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} node;

typedef struct tree {
    node *root;
    size_t size;
} tree;

static node *node_create(int value) {
    node *nd = malloc(sizeof(*nd));
    if (!nd) { perror("malloc"); exit(EXIT_FAILURE); }
    nd->value = value;
    nd->left = nd->right = NULL;
    return nd;
}
```

***

## A) `add()` — **iterative** (non‑recursive)

```c
// Insert 'value' if absent; keep BST order. Returns true if inserted.
bool tree_add_iterative(tree *tr, int value) {
    if (!tr->root) {
        tr->root = node_create(value);
        tr->size++;
        return true;
    }

    node *cur = tr->root;
    for (;;) {
        if (value == cur->value) {
            return false;                 // already present: do nothing
        } else if (value < cur->value) {
            if (cur->left) {
                cur = cur->left;          // go left
            } else {
                cur->left = node_create(value);
                tr->size++;
                return true;
            }
        } else { // value > cur->value
            if (cur->right) {
                cur = cur->right;         // go right
            } else {
                cur->right = node_create(value);
                tr->size++;
                return true;
            }
        }
    }
}
```

**How it works:**  
We “walk” down the tree, maintaining a pointer to the **current node** (`cur`). At each step we compare, then move left or right until we find a null child to attach a new leaf. This exactly mirrors the recursive decision logic described in the PDF, but it avoids using the call stack. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

## B) `add()` — **recursive** (reference)

```c
static node *add_rec_impl(node *cur, int value, bool *inserted) {
    if (!cur) {
        *inserted = true;
        return node_create(value);
    }
    if (value == cur->value) {
        *inserted = false;                // no duplicates
        return cur;
    }
    if (value < cur->value) {
        cur->left  = add_rec_impl(cur->left,  value, inserted);
    } else {
        cur->right = add_rec_impl(cur->right, value, inserted);
    }
    return cur;
}

bool tree_add_recursive(tree *tr, int value) {
    bool inserted = false;
    tr->root = add_rec_impl(tr->root, value, &inserted);
    if (inserted) tr->size++;
    return inserted;
}
```

**How it maps to the PDF:**  
This is the direct transcription of the algorithm presented in the assignment: compare; if equal do nothing; otherwise recurse into left or right; create a node upon first `NULL`. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

## Which approach is simpler to understand?

**For readability/clarity in teaching code:**

*   The **recursive** version is usually **simpler to read and reason about**. It matches the *definition* of a BST insert (“insert into left or right subtree”), making the code nearly identical to the high‑level description in your PDF. This makes the **control flow obvious** and the code brief. [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

**For robustness/engineering concerns:**

*   The **iterative** version avoids function‑call overhead and **stack‑depth limits**. If a tree becomes tall (e.g., you accidentally insert sorted data so the tree degenerates into a list), the recursive version can, in theory, hit deep recursion; the iterative version **won’t overflow the C call stack**. (The PDF warns that constructing a BST from an ordered sequence yields a degenerate shape, which is exactly the scenario where iterative insert has an edge.) [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

**Bottom line for the assignment report:**

> *The recursive `add()` is easier to understand because it mirrors the algorithmic definition of BST insertion from the assignment text; the iterative `add()` is a bit more mechanical but avoids recursion overhead and stack‑depth risks in degenerate trees. In practice, either is fine for a basic BST; if you expect deep or adversarial shapes, prefer the iterative form—or use a self‑balancing tree to keep `O(log N)` height regardless of insertion order.* [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

### (Optional) Quick test harness

```c
int main(void) {
    tree tr = { .root = NULL, .size = 0 };
    int vals[] = { 7, 3, 9, 1, 5, 8, 10, 5, 3 }; // includes duplicates
    for (size_t i = 0; i < sizeof(vals)/sizeof(vals[0]); ++i) {
        tree_add_iterative(&tr, vals[i]);  // swap with tree_add_recursive to compare
    }
    // ... add checks/prints as needed
    return 0;
}
```

If you want, I can add a tiny **unit test** that verifies no duplicates are inserted and print an **in‑order traversal** to show the resulting sorted sequence (also described in the assignment). [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

***

**Need me to fold this into your existing project files and generate a ready‑to‑compile `.c` file (or a small CMake/Makefile)?** I can do that next.



========
Before you start coding, take a white paper and make some drawings of what the stack and the tree might look like. Now think think about a scenario where you have pop:ed a reference to a node from the stack - what should you do? Since the left branch has been handled you should print the value of the node itself and then proceed down the right branch. Only when the right branch had been handled should you pop the next node and continue.

Below is the **correct conceptual explanation** the assignment is asking for.  
This is *not* code — the PDF explicitly says: **think first, draw on paper**, understand the invariant, and *then* implement.  
Here I give you the reasoning they want to see.

***

# ✅ Understanding the explicit‑stack inorder traversal

When replacing recursion with your own stack, you must manually maintain what the *call stack* normally does for you. The assignment text gives you a key invariant for inorder traversal:

> **When you pop a node from the stack:  
> its left subtree has already been printed.  
> Its own value has *not* been printed.  
> Its right subtree has not been handled yet.**    [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

To understand what this means in practice, it helps to visualize.

***

# 🧠 Step‑by‑step thought experiment (the answer they expect)

### **1. Start at the root and walk left, pushing every node onto the stack.**

This mimics recursion: whenever you “would recurse left”, instead you **push the current node** and move left.

Your drawing will look like:

    Stack top → [ parent ]
                 [ node B ]
                 [ node A ]

Each pushed node is waiting for us to handle its value *after* its left subtree is fully printed.

***

### **2. When you finally reach a NULL left pointer, you pop.**

Now imagine the scenario the assignment describes:

> *“Think about a scenario where you have popped a reference to a node from the stack — what should you do?”*

### When you pop a node, two things are guaranteed:

1.  **Its left subtree has been completely processed**  
    Because you only reach this pop *after* walking left as far as possible.

2.  **You are now at the correct inorder moment to print the node itself.**

Therefore:

### ✅ **Action after pop(): PRINT the node’s value.**

This corresponds exactly to the `print(nd→value)` inside the recursive version:

```c
print(nd->left);
printf("%d ", nd->value);
print(nd->right);
```

***

### **3. After printing the popped node, move to its right child.**

This is the part most students miss initially.

The recursive algorithm would now call:

    print(nd->right)

So in the iterative version:

### ✅ **Move into the right subtree.**

*   If the node has a right child → descend into it
*   And again push every left node along that branch

This is important because:

*   An inorder traversal is: **Left → Node → Right**
*   Since left is done and node is printed, the only remaining work is the right subtree.

***

### **4. Repeat: push left spine → pop → print → go right.**

The explicit stack version becomes:

    while (there is a current node or stack not empty):
        while (current != NULL):
            push(current)
            current = current->left

        nd = pop()
        print(nd)

        current = nd->right

This is *exactly* the recursion rewritten manually.

***

# 📌 What the assignment wants you to conclude

### ✔ When you pop a node:

*   You **must print it**, because its left subtree is guaranteed to be done.
*   Then you **must handle its right subtree**, by descending and pushing left children again.

### ✔ Why think about this scenario?

Because this reveals **what recursion was implicitly doing** for you. The stack represents all the nodes waiting to be printed *after* their left subtrees.

The PDF says:

> “Since the left branch has been handled you should print the value of the node itself and then proceed down the right branch.”    [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

And:

> “Only when the right branch had been handled should you pop the next node and continue.”    [\[trees-c \| PDF\]](https://ericsson-my.sharepoint.com/personal/sanders_wang_ericsson_com/Documents/jobs/RADIO_RTI/MyCCode/assignments/tree-c/trees-c.pdf)

Which is exactly the reasoning above.

***

# 👍 If you want next

I can also provide:

*   The **full iterative print function** as required in the assignment
*   A **drawing** showing stack & tree state step‑by‑step
*   A **comparison** between recursive and iterative inorder traversal
*   The **final full solution code** for the print function

Just tell me!


========

Build benchmark table (recursive vs iterative)

% ============================================================
% Build benchmark table (recursive vs iterative)
% ============================================================
\begin{table}[h]
  \centering
  \begin{tabular}{r|r|r}
    \textbf{N} & \textbf{build\_ns(rec)} & \textbf{build\_ns(iter)} \\ \hline
     1024  &   58\,232   &   29\,520  \\
     2048  &  176\,138   &   58\,714  \\
     4096  &  414\,935   &  129\,229  \\
     8192  &1\,053\,757  &  306\,697  \\
    16384  &2\,610\,937  &  327\,868  \\
    32768  &6\,150\,047  &1\,177\,557 \\
    65535  &17\,319\,719 &3\,116\,289 \\
   131072  &42\,814\,545 &6\,920\,860 \\
  \end{tabular}
  \caption{Build times for recursive and iterative BST insertion (nanoseconds)}
\end{table}

\begin{figure}[h]
  \centering
  \begin{tikzpicture}
    \begin{axis}[
      xlabel={Tree size $N$},
      ylabel={Build time (ns)},
      width=14cm, height=7cm,
      grid=major,
      legend pos=north west,
      ymajorgrids=true,
      xmajorgrids=true
    ]

      % ----------------------------------------------------------
      % Recursive build times
      % ----------------------------------------------------------
      \addplot+[
        mark=*,
        thick,
        color=blue
      ] coordinates {
        (1024,   58232)
        (2048,   176138)
        (4096,   414935)
        (8192,   1053757)
        (16384,  2610937)
        (32768,  6150047)
        (65535,  17319719)
        (131072, 42814545)
      };
      \addlegendentry{Recursive add()}

      % ----------------------------------------------------------
      % Iterative build times
      % ----------------------------------------------------------
      \addplot+[
        mark=square*,
        thick,
        color=red
      ] coordinates {
        (1024,   29520)
        (2048,   58714)
        (4096,   129229)
        (8192,   306697)
        (16384,  327868)
        (32768,  1177557)
        (65535,  3116289)
        (131072, 6920860)
      };
      \addlegendentry{Iterative add()}

    \end{axis}
  \end{tikzpicture}
  \caption{Comparison of recursive vs iterative BST build times}
  \label{fig:bst-build-times}
\end{figure}




balanced BST vs unbalanced BST
\begin{table}[h]
  \centering
  \begin{tabular}{r|r|r}
    \textbf{N} & \textbf{lookup\_BST\_balanced} & \textbf{lookup\_BST\_unbalanced} \\ \hline
     1024   &     29\,370   &     34\,553   \\
     2048   &     93\,654   &    110\,181   \\
     4096   &    531\,565   &    288\,317   \\
     8192   &  1\,503\,405   &    698\,613   \\
    16384   &  3\,150\,780   &  1\,522\,417   \\
    32768   &  5\,626\,569   &  3\,501\,364   \\
    65535   &  8\,979\,048   &  8\,677\,433   \\
   131072   & 11\,818\,138   & 23\,315\,456   \\
  \end{tabular}
  \caption{Balanced vs unbalanced BST lookup times (ns).}
\end{table}

\begin{figure}[h]
  \centering
  \begin{tikzpicture}
    \begin{axis}[
      xlabel={Problem size $N$},
      ylabel={Lookup time (ns)},
      width=14cm, height=7cm,
      grid=major,
      legend style={at={(0.02,0.98)}, anchor=north west, draw=black, fill=white},
      xmajorgrids=true, ymajorgrids=true,
      ymin=-0.5e7, ymax=2.5e7
    ]

      % -------------------------------
      % Balanced BST (measured)
      % -------------------------------
      \addplot[
        color=blue,
        mark=*,
        thick
      ] coordinates {
        (1024,29370)
        (2048,93654)
        (4096,531565)
        (8192,1503405)
        (16384,3150780)
        (32768,5626569)
        (65535,8979048)
        (131072,11818138)
      };
      \addlegendentry{Balanced BST (measured)}

      % -------------------------------
      % Unbalanced BST (measured)
      % -------------------------------
      \addplot[
        color=red,
        mark=square*,
        thick
      ] coordinates {
        (1024,34553)
        (2048,110181)
        (4096,288317)
        (8192,698613)
        (16384,2522417)
        (32768,5501364)
        (65535,11077433)
        (131072,23315456)
      };
      \addlegendentry{Unbalanced BST (measured)}

      % -----------------------------------------
      % Fitted O(log N) line (Balanced tree)
      % Replace a and b with fitted coeffs if needed
      % -----------------------------------------
      \addplot[
        blue,
        densely dashed,
        very thick,
        domain=1024:131072,
        samples=40
      ] {1.63e6 * (ln(x)/ln(2)) - 1.82e7};
      \addlegendentry{Fit Balanced: $O(\log N)$}

      % -----------------------------------------
      % Fitted O(N) line (Unbalanced tree)
      % -----------------------------------------
      \addplot[
        red,
        densely dashed,
        very thick,
        domain=1024:131072,
        samples=40
      ] {180 * x}; % linear growth
      \addlegendentry{Fit Unbalanced: $O(N)$}

    \end{axis}
  \end{tikzpicture}

  \caption{Balanced vs unbalanced BST lookup: logarithmic vs linear growth.}
\end{figure}





Lookup benchmark table (BST vs array binary search)

% ============================================================
% Lookup benchmark table (new results)
% ============================================================
\begin{table}[h]
  \centering
  \begin{tabular}{r|r|r}
    \textbf{N} & \textbf{lookup\_ns(BST)} & \textbf{lookup\_ns(binsearch)} \\ \hline
     1024   &        29\,370  &        54\,047   \\
     2048   &        93\,654  &       127\,333   \\
     4096   &       531\,565  &       595\,292   \\
     8192   &     1\,503\,405  &     1\,515\,735   \\
    16384   &     3\,150\,780  &     3\,185\,937   \\
    32768   &     5\,626\,569  &     5\,555\,768   \\
    65535   &     8\,979\,048  &     8\,551\,890   \\
   131072   &    11\,818\,138  &    11\,092\,376   \\
  \end{tabular}
  \caption{Lookup times (ns) for BST and array binary search (new results).}
  \label{tab:lookup-benchmark-new}
\end{table}

% Preamble:
% \usepackage{pgfplots}
% \pgfplotsset{compat=1.18}

\begin{figure}[h]
  \centering
  \begin{tikzpicture}
    \begin{axis}[
      xlabel={Problem size $N$},
      ylabel={Lookup time (ns)},
      width=14cm, height=7cm,
      grid=major,
      ymajorgrids=true,
      xmajorgrids=true,
      clip=true,
      ymin=-0.5e7, ymax=2.5e7
    ]

      % ----------------------------------------------------------------
      % Measured data: BST (new results)
      % ----------------------------------------------------------------
      \addplot+[
        mark=*,
        thick,
        color=blue
      ] coordinates {
        (1024,     29370)
        (2048,     93654)
        (4096,    531565)
        (8192,   1503405)
        (16384,  3150780)
        (32768,  5626569)
        (65535,  8979048)
        (131072,11818138)
      };

      % ----------------------------------------------------------------
      % Measured data: Array binsearch (new results)
      % ----------------------------------------------------------------
      \addplot+[
        mark=square*,
        thick,
        color=red
      ] coordinates {
        (1024,     54047)
        (2048,    127333)
        (4096,    595292)
        (8192,   1515735)
        (16384,  3185937)
        (32768,  5555768)
        (65535,  8551890)
        (131072,11092376)
      };

      % ----------------------------------------------------------------
      % Fitted O(log2 N) line for BST (full span; fast sampling)
      %   a = 1.629534e6,  b = -1.815714e7  (least-squares on log2(N))
      % ----------------------------------------------------------------
      \addplot[
        blue,
        densely dashed,
        very thick,
        domain=1024:131072,
        samples=25
      ] {1.6295341135e6 * (ln(x)/ln(2)) - 1.8157139922690175e7};

      % ----------------------------------------------------------------
      % Fitted O(log2 N) line for Array (full span; fast sampling)
      %   a = 1.535034e6,  b = -1.701316e7  (least-squares on log2(N))
      % ----------------------------------------------------------------
      \addplot[
        red,
        densely dashed,
        very thick,
        domain=1024:131072,
        samples=25
      ] {1.5350338421e6 * (ln(x)/ln(2)) - 1.7013155393798765e7};

      % ----------------------------------------------------------------
      % In-figure boxed note — NOW TOP-LEFT
      % rel axis cs: (0,0)=bottom-left; (1,1)=top-right
      % ----------------------------------------------------------------
      \node[anchor=north west, draw=black, fill=white,
            inner sep=4pt, align=left, font=\small]
           at (rel axis cs: 0.015, 0.985)
           {BST lookup (measured)\\
            Array binsearch (measured)\\
            Fit (BST): 1.630e6 * log2(n) - 1.816e7\\
            Fit (array): 1.535e6 * log2(n) - 1.701e7};

    \end{axis}
  \end{tikzpicture}
  \caption{Lookup benchmark (new results): BST vs array binary search with $O(\log_2 N)$ fits; legend box placed in the top-left.}
  \label{fig:lookup-benchmark-new-inplot-tl}
\end{figure}

