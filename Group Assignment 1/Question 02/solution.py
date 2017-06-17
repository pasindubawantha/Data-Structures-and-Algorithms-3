class Node:#for Tree data structure
	leftChild = None;
	rightSibling = None;
	name = None;
	rating = None;
	invite = None;

	def __init__(self, leftChild, rightSibling, name, rating):
		self.leftChild = leftChild;
		self.rightSibling = rightSibling;
		self.name = name;
		self.rating = rating;

class Queue:
	queue = []
	def __init__(self):
		self.queue = []
		return None
	def enqueue(self, value):
		self.queue.append(value)
	def dequeue(self):
		if self.isEmpty():
			return None
		else:
			return self.queue.pop(0)
	def isEmpty(self):
		return self.queue == []

class Stack:
	stack = []
	def __init__(self):
		self.stack = []
		return None
	def isEmpty(self):
		return self.stack == []
	def push(self, value):
		self.stack.append(value)
	def pop(self):
		if self.isEmpty():
			return None
		else:
			return self.stack.pop(-1)

class Tree:#to represent company organizational hierachy of employees
	root = None;
	def __init__(self):
		self.root = None
		return None 

	def insertNode(self, childName, childRating, parentName=None):
		node = Node(None, None, childName, childRating)
		if parentName is None:
			self.root = node
		else:
			parentNode = self.searchNode(parentName)
			if parentNode is None:
				print('Failed to insert "'+ childName +'" : No parent node named "'+ parentName +'"')
			else:
				childNode = self.searchNode(childName)
				if childNode is None:
					if parentNode.leftChild is None:
						parentNode.leftChild = node
					else:
						sibling = parentNode.leftChild
						while not sibling.rightSibling is None:
							sibling = sibling.rightSibling
						sibling.rightSibling = node
				else:
					print('Failed to insert "'+ childName +'" : "'+ childName +'" node already exists')

	def searchNode(self, nodeName):
		queue = Queue()
		queue.enqueue(self.root)
		currentNode = self.root
		if self.root.name == nodeName:
			return self.root
		nodeFound = None
		while nodeFound is None and (not queue.isEmpty()):
			currentNode = queue.dequeue()
			if not currentNode is None:
				currentNode = currentNode.leftChild
				if not currentNode is None:
					queue.enqueue(currentNode)
					if currentNode.name == nodeName:
						nodeFound = currentNode
					while (not currentNode.rightSibling is None) and (nodeFound is None):
						currentNode = currentNode.rightSibling
						queue.enqueue(currentNode)
						if currentNode.name == nodeName:
							nodeFound = currentNode
		return nodeFound 

	def printTree(self):
		queue = Queue()
		queue.enqueue(self.root)
		currentNode = self.root
		print(currentNode.name + ':' + str(currentNode.rating))
		line = ''
		while not queue.isEmpty():
			currentNode = queue.dequeue()
			if not currentNode is None:
				currentNode = currentNode.leftChild
				if not currentNode is None:
					queue.enqueue(currentNode)
					line += currentNode.name + ':' + str(currentNode.rating)
				
					while not currentNode.rightSibling is None:
						currentNode = currentNode.rightSibling
						queue.enqueue(currentNode)
						line += ' ' + currentNode.name + ':' + str(currentNode.rating)
					print(line)
					line = ''


def getRatingSumOfChildren(parent):
	currentNode = parent.leftChild
	ratingSum = 0.0
	while not currentNode is None:
		ratingSum += currentNode.rating
		currentNode = currentNode.rightSibling
	return ratingSum

def getRatingSumOfGrandChildren(parent):
	ratingSum = 0.0
	child = parent.leftChild
	while not child is None:
		grandChild = child.leftChild
		while not grandChild is None:
			ratingSum += grandChild.rating
			grandChild = grandChild.rightSibling
		child = child.rightSibling
	return ratingSum



def solve(tree):
	#preprosessing
	stack =  Stack() #to acesses the tree from bottom to top
	queue = Queue()
	queue.enqueue(tree.root)
	stack.push(tree.root)
	currentNode = tree.root
	while not queue.isEmpty():
		currentNode = queue.dequeue()
		if not currentNode is None:
			currentNode = currentNode.leftChild
			if not currentNode is None:
				queue.enqueue(currentNode)
				stack.push(currentNode)
				while not currentNode.rightSibling is None:
					currentNode = currentNode.rightSibling
					queue.enqueue(currentNode)
					stack.push(currentNode)
	while(not stack.isEmpty()):#calculate maximum possible rating for each sub tree intiating from Node
		currentNode = stack.pop()
		childrenRatingSum = getRatingSumOfChildren(currentNode)
		grandChildrenRatingSum = getRatingSumOfGrandChildren(currentNode)
		if( (currentNode.rating + grandChildrenRatingSum) >= childrenRatingSum ):
			currentNode.invite = True
			currentNode.rating += grandChildrenRatingSum
		else:
			currentNode.invite = False
			currentNode.rating = childrenRatingSum
	
	#Create invite list
	inviteList = []
	queue = Queue()
	queue.enqueue(tree.root)
	currentNode = tree.root
	if(currentNode.invite):
		inviteList.append(currentNode.name)
		childNode = currentNode.leftChild
		while not childNode is None:
			childNode.invite = False
			childNode = childNode.rightSibling
	while not queue.isEmpty():
		currentNode = queue.dequeue()
		if not currentNode is None:
			currentNode = currentNode.leftChild
			if not currentNode is None:
				queue.enqueue(currentNode)
				if(currentNode.invite):
					inviteList.append(currentNode.name)
					childNode = currentNode.leftChild
					while not childNode is None:
						childNode.invite = False
						childNode = childNode.rightSibling
				while not currentNode.rightSibling is None:
					currentNode = currentNode.rightSibling
					queue.enqueue(currentNode)
					if(currentNode.invite):
						inviteList.append(currentNode.name)
						childNode = currentNode.leftChild
						while not childNode is None:
							childNode.invite = False
							childNode = childNode.rightSibling
	return inviteList


##Testing code

def test1() :
	testTree1 = Tree()
	testTree1.insertNode('president', 100)
	testTree1.insertNode('employee1', 100,'president')#not invited
	testTree1.insertNode('employee2', 200,'president')#not invited

	testTree1.insertNode('employee3', 300,'employee1')
	testTree1.insertNode('employee4', 100,'employee1')

	testTree1.insertNode('employee5', 200,'employee2')
	testTree1.insertNode('employee6', 100,'employee2')

	testTree1.insertNode('employee7', 200,'employee3')
	testTree1.insertNode('employee8', 200,'employee3')
	testTree1.insertNode('employee9', 200,'employee3')

	testTree1.insertNode('employee10', 200,'employee5')
	testTree1.insertNode('employee11', 200,'employee5')

	testTree1.insertNode('employee12', 200,'employee7')
	testTree1.insertNode('employee13', 200,'employee7')

	print("Running test case 1 :")
	print("Tree structure :")
	print("")
	print("						                                 president:100")
	print("                                                          /          \ ")
	print("                                                       /                \ ")
	print("                                                    /                      \ ")
	print("                                                 /                            \ ")
	print("                                              /                                  \ ")
	print("				                    employee1:100                                employee2:200")
	print("			                          /        \                                   /      \ ")
	print("		                    employee3:300    employee4:100              employee5:200    employee6:100")
	print("		                    /    |      \                                   /      \ ")
	print("                        /       |         \                             /            \ ")
	print("                     /          |            \                       /                  \ ")
	print("	       employee7:200    employee8:200    employee9:200     employee10:200    employee11:200")
	print("	         /       \ ")
	print("employee12:200    employee13:200")
	print("")
	print("Solution : Invitee list ;")
	print(solve(testTree1)) 

def main():
	test1()

main()


