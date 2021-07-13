/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
	//Itialize the root as nullptr
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{

	//Deletes the root
	while (m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const
{
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	//Inserts the value into the new node
	TreeNode* pNode = new TreeNode(a_nValue);

	//Bool so the while loop will run
	bool run = true;

	//Is the Tree is empty enter
	if (IsEmpty())
	{
		//Sets the node at the root
		m_pRoot = pNode;
	}

	else
	{
		//Creates a new node that equal to the root
		TreeNode* pCurrentNode = m_pRoot;
		while (run)
		{
			//If the value in pNode is smaller than the value in pCurrentNode enter
			if (pNode->GetData() < pCurrentNode->GetData())
			{
				//pCurrentNode has a left node is true enter
				if (pCurrentNode->HasLeft() == 1)
				{
					//pCurrentNode equals to the left child node of pCurrentNode
					pCurrentNode = pCurrentNode->GetLeft();
				}
				
				//Else if pCurrent node doesn't have a left node enter
				else if (pCurrentNode->HasLeft() == 0)
				{
					//Creates a left child node for pCurrentNode where pNode in inserted
					pCurrentNode->SetLeft(pNode);
					
					//Set the bool to flase ending the while loop
					run = false;
				}
			}

			//If the value in pNode is greater than the value in pCurrentNode enter
			if (pNode->GetData() > pCurrentNode->GetData())
			{
				//pCurrentNode equals to the right child node of pCurrentNode
				if (pCurrentNode->HasRight() == 1)
				{
					//pCurrentNode equals to the right child node of pCurrentNode
					pCurrentNode = pCurrentNode->GetRight();
				}

				//Else if pCurrent node doesn't have a right node enter
				else if (pCurrentNode->HasRight() == 0)
				{
					//Creates a right child node for pCurrentNode where pNode in inserted
					pCurrentNode->SetRight(pNode);

					//Set the bool to flase ending the while loop
					run = false;
				}
			}
		}
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	//ppOutNode equals the root
	ppOutNode = m_pRoot;

	//ppOutParent equals ppOutNode
	ppOutParent = ppOutNode;

	//ppOutNode doesn't equal false
	while (ppOutNode != nullptr)
	{
		//The search value equals ppOutNode value
		if (a_nSearchValue == ppOutNode->GetData())
		{
			//return the TreeNodes
			return ppOutNode, ppOutParent;
		}
		
		//The search value smaller than ppOutNode value
		else if (a_nSearchValue < ppOutNode->GetData())
		{
			//ppOutParent equals ppOutNode
			ppOutParent = ppOutNode;

			//ppOutNode equals ppOutNode left child
			ppOutNode = ppOutNode->GetLeft();
		}

		else
		{
			//ppOutParent equals ppOutNode
			ppOutParent = ppOutNode;

			//ppOutNode equals ppOutNode right child
			ppOutNode = ppOutNode->GetRight();
		}
	}

	//ppOutNode did equal false
	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	//Creates the Nodes needed for the remove function
	TreeNode* pCurrentNode = nullptr;
	TreeNode* pParentNode = nullptr;
	TreeNode* pNewNode = nullptr;
	TreeNode* pDeleteParent = nullptr;

	//Using the int value to find the pCurrentNode with the same value and its pParentNode
	FindNode(a_nValue, pCurrentNode, pParentNode);

	//Deleting single node
	//pCurrentNode doesn't has a left or right child node 
	if (pCurrentNode->GetLeft() == nullptr && pCurrentNode->GetRight() == nullptr)
	{
		//pParentNode left child equal pCurrentNode
		if (pParentNode->GetLeft() == pCurrentNode)
		{
			//Sets pParentNode left child nullptr
			pParentNode->SetLeft(nullptr);
		}

		//pParentNode left child equal pCurrentNode
		if (pParentNode->GetRight() == pCurrentNode)
		{
			//Sets pParentNode left child nullptr
			pParentNode->SetRight(nullptr);
		}

		//Deletes pCurrentNode
		delete pCurrentNode;
	}

	//Deleting Node with two children
	//pCurrentNode has a left and right child node
	else if (pCurrentNode->HasLeft() && pCurrentNode->HasRight())
	{
		//pParentNode equals pCurrentNode
		pParentNode = pCurrentNode;
		//pCurrentNode equals pCurrentNode rigth child
		pCurrentNode = pCurrentNode->GetRight();

		//Bool to run the while loop
		bool run = true;

		while (run)
		{
			//pCurrentNode has a left child
			if (pCurrentNode->HasLeft())
			{
				//pDeleteParent equals pCurrentNode
				pDeleteParent = pCurrentNode;

				//pCurrentNode equals pCurrentNode left child
				pCurrentNode = pCurrentNode->GetLeft();
			}

			//Else pCurrentNode doesn't have a left child
			else if (pCurrentNode->HasLeft() == false)
			{
				//pParentNode value to pCurrentNode value
				pParentNode->SetData(pCurrentNode->GetData());

				//Set bool to false to end while loop
				run = false;
			}
		}

		//pCurrentNode doesn't have a right child
		if (pCurrentNode->HasRight() == false)
		{
			//delete pCurrentNode
			delete pCurrentNode;

			//Set pParentNode right child to nullptr
			pParentNode->SetRight(nullptr);
		}

		//pCurrentNode has a right child
		else if (pCurrentNode->HasRight())
		{
			//pNewNode = pCurrentNode right child
			pNewNode = pCurrentNode->GetRight();

			//Set pDeleteParent left child to pNewNode
			pDeleteParent->SetLeft(pNewNode);

			//delete pCurrentNode
			delete pCurrentNode;
		}
	}

	//pCurrentNode has at least a left or right child
	else if (pCurrentNode->HasLeft() || pCurrentNode->HasRight())
	{
		//pCurrentNode does have a left child
		if (pCurrentNode->GetLeft() != nullptr)
		{
			//pNewNode equals pCurrentNode left child
			pNewNode = pCurrentNode->GetLeft();
		}

		//pCurrentNode does have a right child
		else if (pCurrentNode->GetRight() != nullptr)
		{
			//pNewNode equals pCurrentNode left child
			pNewNode = pCurrentNode->GetRight();
		}

		//pParentNode left child equals pCurrentNode
		if (pParentNode->GetLeft() == pCurrentNode)
		{
			//Set pParentNode left child to pNewNode
			pParentNode->SetLeft(pNewNode);
		}

		//pParentNode right child equals pCurrentNode
		else if (pParentNode->GetRight() == pCurrentNode)
		{
			//Set pParentNode right child to pNewNode
			pParentNode->SetRight(pNewNode);
		}
	}
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
	PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{

	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);

			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}