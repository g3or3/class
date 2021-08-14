class Node:
    def __init__(self, v):
        # for LL, Stack, Queue
        self.val = v
        self.next = None

        # for BST
        self.left = None
        self.right = None


class Stack:
    def __init__(self):
        self.head = None

    def push(self, v):
        if not self.head:
            self.head = Node(v)
            return

        newNode = Node(v)
        newNode.next = self.head
        self.head = newNode

    def pop(self):
        if not self.head:
            return

        popped = self.head
        self.head = popped.next
        popped.next = None

        return popped

    def peek(self):
        if not self.head:
            return

        print(self.head.value)

    def printStack(self):
        curr = self.head

        while curr:
            print(curr.val)
            curr = curr.next


class Queue:
    def __init__(self):
        self.head = None
        self.tail = None

    def enqueue(self, v):
        newNode = Node(v)

        if not self.head:
            self.head = self.tail = newNode
            return

        self.tail.next = newNode
        self.tail = newNode

    def dequeue(self):
        if not self.head:
            return

        dequeued = self.head
        self.head = dequeued.next
        dequeued.next = None

        return dequeued

    def isEmpty(self):
        return self.head == None

    def printQueue(self):
        curr = self.head

        while curr:
            print(curr.val)
            curr = curr.next


class BST:
    def __init__(self):
        self.root = None

    def insert(self, v):
        if not self.root:
            self.root = Node(v)
            return

        root = self.root

        """
        Iterative approach
        """

        # while root:
        #     prev = root
        #     if v < root.val:
        #         root = root.left
        #         if not root:
        #             prev.left = Node(v)
        #     else:
        #         root = root.right
        #         if not root:
        #             prev.right = Node(v)

        """
        Recursive approach
        """

        def helper(root, v):
            if not root:
                root = Node(v)
                return root

            if v < root.val:
                root.left = helper(root.left, v)

            elif v > root.val:
                root.right = helper(root.right, v)

            return root

        helper(root, v)

    def remove(self, target):
        if not self.root:
            return

        root = self.root

        if root.val == target:
            if root.left and root.right:
                curr = root.right

                while curr.left:
                    curr = curr.left

                curr.left = root.left
                self.root = root.right
                root.left = None
                root.right = None

            elif root.left:
                self.root = root.left
                root.left = None

            else:
                self.root = root.right
                root.right = None

            return root.val

        def helper(root, target, parent=None):
            if not root:
                return

            if root.val == target:
                if not root.left and not root.right:
                    if parent.val > root.val:
                        parent.left = None

                    else:
                        parent.right = None

                elif root.left and not root.right:
                    if parent.val > root.val:
                        parent.left = root.left

                    else:
                        parent.right = root.left

                elif root.right and not root.left:
                    if parent.val < root.val:
                        parent.right = root.right

                    else:
                        parent.left = root.right

                else:
                    if parent.val > root.val:
                        parent.left = root.right

                        curr = root.right

                        while curr.left:
                            curr = curr.left

                        curr.left = root.left
                    else:
                        parent.right = root.right

                        curr = root.right

                        while curr.left:
                            curr = curr.left

                        curr.left = root.left

                temp = root.val
                root.left = root.right = None
                return temp

            if target < root.val:
                return helper(root.left, target, root)

            else:
                return helper(root.right, target, root)

        return helper(root, target)

    def getHeight(self):
        root = self.root

        def helper(root):
            if not root:
                return 0

            return max(helper(root.left), helper(root.right)) + 1

        return helper(root)

    def printBFT(self):
        q = Queue()
        q.enqueue(self.root)

        while not q.isEmpty():
            curr = q.dequeue().val

            if curr.left:
                q.enqueue(curr.left)
            if curr.right:
                q.enqueue(curr.right)

            print(curr.val)

    def inOrderPrint(self):
        root = self.root

        def helper(root):
            if not root:
                return

            helper(root.left)
            print(root.val)
            helper(root.right)

        helper(root)


class Vertex:
    def __init__(self, v):
        self.val = v
        self.edges = []

    def addEdge(self, vertex):
        self.edges.append(vertex)

    def removeEdge(self, vertex):
        self.edges.remove(vertex)

    def printEdges(self):
        print(f"{self.val}: {[vertex.val for vertex in self.edges]}")


class Graph:
    def __init__(self):
        self.vertices = {}

    def addVertex(self, v):
        if not v in self.vertices:
            self.vertices[v] = Vertex(v)

    def addEdge(self, v1, v2):
        if not v1 in self.vertices:
            self.addVertex(v1)
        if not v2 in self.vertices:
            self.addVertex(v2)
        self.vertices[v1].addEdge(self.vertices[v2])

    def printGraph(self):
        for vertex in self.vertices.values():
            vertex.printEdges()
