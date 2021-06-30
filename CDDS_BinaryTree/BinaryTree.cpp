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
	m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
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
	TreeNode* pNode = new TreeNode(a_nValue);
	bool run = true;

	if (IsEmpty())
	{
		m_pRoot = pNode;
	}

	else
	{
		TreeNode* pCurrentNode = m_pRoot;
		while (run)
		{
			if (pNode->GetData() < pCurrentNode->GetData())
			{
				if (pCurrentNode->HasLeft() == 1)
				{
					pCurrentNode = pCurrentNode->GetLeft();
				}
				
				if (pCurrentNode->HasLeft() == 0)
				{
					pCurrentNode->SetLeft(pNode);
					run = false;
				}
			}

			if (pNode->GetData() > pCurrentNode->GetData())
			{
				if (pCurrentNode->HasRight() == 1)
				{
					pCurrentNode = pCurrentNode->GetRight();
				}

				if (pCurrentNode->HasRight() == 0)
				{
					pCurrentNode->SetRight(pNode);
					run = false;
				}
			}
		}
	}

	//else
	//{
	//	TreeNode* pCurrentNode = m_pRoot;
	//	while (pCurrentNode != nullptr)
	//	{
	//		if (a_nValue < pCurrentNode->GetData())
	//		{
	//			pCurrentNode->SetLeft(pCurrentNode);
	//		}

	//		if (a_nValue > pCurrentNode->GetData())
	//		{
	//			pCurrentNode->SetRight(pCurrentNode);
	//		}

	//		if (a_nValue == pCurrentNode->GetData())
	//		{
	//			break;
	//		}
	//	}

	//	TreeNode* pParent = pCurrentNode;
	//	if (a_nValue < pParent->GetData())
	//	{
	//		pCurrentNode->SetData(a_nValue);
	//	}
	//	else
	//	{
	//		pCurrentNode->SetData(a_nValue);
	//	}
	//}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent : nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	 ppOutNode = m_pRoot;

	while (ppOutNode != nullptr)
	{
		if (a_nSearchValue == ppOutNode->GetData())
		{
			return ppOutNode, ppOutParent;
		}
		
		else if (a_nSearchValue < ppOutNode->GetData())
		{
			ppOutNode = ppOutNode->GetLeft();
		}

		else
		{
			ppOutNode = ppOutNode->GetRight();
		}
	}


	/*ppOutNode = m_pRoot;
	while (ppOutNode != nullptr)
	{
		if (a_nSearchValue == ppOutNode->GetData())
		{
			return ppOutNode, ppOutParent;
		}
		else
		{
			if (a_nSearchValue < ppOutNode->GetData())
			{
				ppOutNode->SetLeft(ppOutNode);
			}
			else
			{
				ppOutNode->SetRight(ppOutNode);
			}
		}
	}
	if (true)
	{
		return false;
	}*/

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	TreeNode* pCurrentNode = nullptr;
	TreeNode* pParentNode = nullptr;

	FindNode(a_nValue, pCurrentNode, pParentNode);

	if (pCurrentNode->GetLeft() == nullptr && pCurrentNode->GetLeft() == nullptr)
	{
		if (pParentNode->GetLeft() == pCurrentNode)
		{
			pParentNode->SetLeft(nullptr);
		}

		if (pParentNode->GetRight() == pCurrentNode)
		{
			pParentNode->SetRight(nullptr);
		}

		delete pCurrentNode;
	}

	/*TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	FindNode(a_nValue, pCurrent, pParent);

	TreeNode* pMinimum = pCurrent->GetRight();

	if (pCurrent->HasRight())
	{
		while (pMinimum->HasLeft())
		{
			pParent = pMinimum;
			pMinimum = pMinimum->GetLeft();
		}

		pCurrent = pMinimum;

		if (pParent->GetLeft() == pMinimum)
		{
			pParent->SetLeft(pMinimum->GetRight());
		}

		if (pParent->GetRight() == pMinimum)
		{
			pParent->SetRight(pMinimum->GetRight());
		}
	}

	if (!pCurrent->HasRight())
	{
		if (pParent->GetLeft() != nullptr)
		{
			pParent->SetLeft(pCurrent->GetLeft());
		}

		if (pParent->GetRight() == pCurrent)
		{
			pParent->SetRight(pCurrent->GetLeft());
		}

		if (pParent == pCurrent)
		{
			pCurrent->SetLeft(pParent);
		}

	}*/

	/*if (pCurrent->GetLeft() == nullptr && pCurrent->GetRight() == nullptr)
	{
		if (pParent->GetLeft() == pCurrent)
			pParent->SetLeft(nullptr);
		if (pParent->GetRight() == pCurrent)
			pParent->SetRight(nullptr);

		delete pCurrent;
	}*/
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