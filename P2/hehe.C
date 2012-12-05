#ifndef __TWO_THREE_TREE_C__
#define __TWO_THREE_TREE_C__

template <class Key, class Val>
static bool IsThreeNode(Node<Key,Val>* node)
{
	if (node->rkey==NULL) return false;
	return true;
}

template <class Key, class Val>
static Val* search_help(Node<Key,Val>* node,Key key)
{
	if (!node) return NULL;
	if (key==*(node->lkey)) return node->lval;
	if ((node->rkey!=NULL)&&(key==*(node->rkey))) return node->rval;
	if (IsThreeNode(node)) {
		if (key<*(node->lkey)) {
			return search_help(node->left,key);
		}else if (key>*(node->rkey)) {
			return search_help(node->right,key);
		}else {
			return search_help(node->center,key);
		}
	}else {
		if (key<*(node->lkey)) {
			return search_help(node->left,key);
		} else {
			return search_help(node->center,key);
		}
	}
}

template <class Key, class Val>
static void copytreenode(Node<Key,Val>* node,Node<Key,Val>* target)
{
	if (target==NULL) {
		node=NULL;	
		return;
	}
	node->left=target->left;
	node->right=target->right;
	node->center=target->center;
	node->lkey=target->lkey;
	node->lval=target->lval;
	node->rkey=target->rkey;
	node->rval=target->rval;
	copytreenode (node->left,target->left);
	copytreenode (node->center,target->center);
	if (IsThreeNode(target)) {
		copytreenode (node->right,target->right);
	}
}

template <class Key, class Val>
static void removetreenode(Node<Key,Val>* node)//slightly different from other recursive
{
	if ((node->left==NULL)&&(node->right==NULL)&&(node->center==NULL)) {
		return;
	}
	removetreenode(node->left);
	delete node->left;
	removetreenode(node->center);
	delete node->center;
	if (IsThreeNode(node)) {
		removetreenode(node->right);
		delete node->right;
	}
}
	

template <class Key, class Val>
Val* Tree<Key,Val>::search(Key key) const
{
	return search_help(root,key);
}

template <class Key, class Val>
static bool inordersuccessor_and_delete(Node<Key,Val>* &node,  Key* &key, Val* &val)//
{
	while (node->left!=NULL) 
	{
		node=node->left;
	}
	key=node->lkey;
	val=node->lval;
	node->lkey=node->rkey;
	node->lval=node->rval;
	node->rkey=NULL;
	node->rval=NULL;
	return (node->lkey==NULL);
}

template <class Key, class Val>
static bool fixinorder(Node<Key,Val>* node)
{
    if (node->left==NULL) {
        return true;
    }

    if (fixinorder(node->left)) {
        return fix_left(node);
    }

    return false;
}

template <class Key, class Val>
static bool fix_left(Node<Key,Val>* node)//4 conditions in all
//the left of the node needs to be fixed
{
	Node<Key,Val>* node_left = node->left;
	Node<Key,Val>* node_center = node->center;

	//center is a 3-node
	//contain 2 conditions: parent 2-node & center child 3-node
	//			parent 3-node & center child 3-node
	if (node_center->rkey!=NULL) {
		node_left->lkey = node->lkey;
		node_left->lval = node->lval;
		node->lkey = node_center->lkey;
		node->lval = node_center->lval;
		node_center->lkey = node_center->rkey;
		node_center->lval = node_center->rval;
		node_center->rkey = NULL;
		node_center->rval = NULL;
		node_left->center = node_center->left;
		node_center->left = node_center->center;
 		node_center->center = node_center->right;
		node_center->right = NULL;
        	return false;
	}

	//center is a 2-node
	//contain 2 conditions: parent 2-node & center child 2-node
	//			parent 3-node & center child 2-node
	node_left->lkey = node->lkey;
	node_left->lval = node->lval;
	node_left->rkey = node_center->lkey;
	node_left->rval = node_center->lval;
	node_center->lkey = NULL;
	node_center->lval = NULL;
	node_left->center = node_center->left;
	node_left->right = node_center->center;
	node_center->left = NULL;
	node_center->center = NULL;
	node_center->right = NULL;

	node->lkey = node->rkey;
	node->lval = node->rval;
	node->rkey= NULL;
	node->rkey= NULL;
	node->center = node->right;
	node->right = NULL;

	delete node_center;
	return (node->lkey==NULL);
}

template <class Key, class Val>
static bool fix_center(Node<Key,Val> *node)//4 conditions in all
//the center of the node needs to be fixed
{
	Node<Key,Val> *node_left = node->left;
	Node<Key,Val> *node_center = node->center;
    
	//left is a 3-node
	//contain 2 conditions: parent 2-node & left child 3-node
	//			parent 3-node & left child 3-node
	if (node_left->rkey !=NULL) 
	{
		node_center->lkey = node->lkey;
		node_center->lval = node->lval;
		node->lkey = node_left->rkey;
		node->lval = node_left->rval;
		node_left->rkey = NULL;
		node_left->rkey = NULL;

		node_center->center = node_center->left;
		node_center->left = node_left->right;
		node_left->right = NULL;

		return false;
	}

	//left is a 2-node
	//contain 1 conditions: parent 3-node & left child 2-node
	if ( node->rkey !=NULL) 
	{
		node_left->rkey = node->lkey;
		node_left->rval = node->lval;
		node->lkey = node->rkey;
		node->lval = node->rval;
		node->rval =NULL;
		node->rkey = NULL;
		node_left->right = node_center->left;
		node_center->left = NULL;
		node->center=node->right;
		node->right= NULL;

		delete node_center;

		return false;
	}

	//left is a 2-node
	//contain 1 conditions: parent 2-node & left child 2-node
	node_left->rkey = node->lkey;
	node_left->rval = node->lval;
	node->lkey=NULL;
	node->lval=NULL;

	node_left->right = node_center->left;
	node_center->left = NULL;
	node->center = NULL;

	delete node_center;

	return true;
}

template <class Key, class Val>
static void fix_right(Node<Key,Val> *node)//2 conditions in all
//the right of the 3-node needs to be fixed
{
	Node<Key,Val>* node_center = node->center;
	Node<Key,Val>* node_right = node->right;

	//center is a 3-node
	//contain 1 conditions: parent 3-node & center child 3-node
	if (node_center->rkey!=NULL) 
	{
		node_right->lkey= node->rkey;
		node_right->lval= node->rval;
		node->rkey = node_center->rkey;
		node->rval = node_center->rval;
		node_center->rval= NULL;
		node_center->rkey= NULL;

		node_right->center = node_right->left;
		node_right->left = node_center->right;
		node_center->right = NULL;
	}
	//center is a 2-node
	//contain 1 conditions: parent 3-node & center child 2-node
	else 
	{
		node_center->rkey = node->rkey;
		node_center->rval = node->rval;
		node->rkey= NULL;
		node->rval=NULL;
		node_center->right = node_right->left;
		node_right->left = NULL;
		node->right = NULL;

		delete node_right;
	}
}

template <class Key, class Val>
static bool remove_help(Node<Key,Val>* node, Key &key, Val &val)
{
	if (node->left!=NULL) //interior node
	{
		if (key<*(node->lkey)) //left
		{
			bool a=remove_help(node->left, key,val);
			if (a) //become 1-node at left
			{
                		return fix_left(node);
			}
		}
		else if (key==*(node->lkey)) //lkey
		{
			Key* succ_key;
			Val* succ_val;
			bool b=inordersuccessor_and_delete(node->center, succ_key, succ_val);
			node->lkey=succ_key;
			node->lval=succ_val;
			if (b) //become 1-node at center
			{
				if (fixinorder(node->center)) 
				{
					return fix_center(node);
                		}
			}
		}
		//others situation:rkey,center,right at 3-node
		else if (node->rkey!=NULL) //3-node
		{
			if (key<*(node->rkey)) //center at 3-node
			{
				bool a=remove_help(node->center, key,val);
				if (a) //become 1-node at center
				{
                			return fix_center(node);
				}
           		}
			else if (key > *(node->rkey)) //right at 3-node
			{
				bool a=remove_help(node->right, key,val);
				if (a) //become 1-node at right
				{
					fix_right(node);
					return false;
				}
			}
            		else //rkey of 3-node
			{
                		Key* succ_key;
				Val* succ_val;
				bool b=inordersuccessor_and_delete(node->right, succ_key, succ_val);
				node->rkey=succ_key;
				node->rval=succ_val;
                		if (b) 
				{
                    			if (fixinorder(node->right)) 
					{
                        			fix_right(node);
                        			return false;
					}
				}
			}
		}

		//2-node, must be center
		else {
			bool a=remove_help(node->center, key, val);
			if (a)
			{
				return fix_center(node);
			}
		}
	}

	//leaf node
	else 
	{
		if (key==*(node->lkey)) //lkey of 2-node or 3-node
		{
			node->lkey=node->rkey;
			node->lval=node->rval;
			node->rkey=NULL;
			node->rval=NULL;
			node->right=NULL;
            		return (node->lkey==NULL);
		}
        	else if ((node->rkey!=NULL)&&(*(node->rkey)==key))//rkey of 3-node
		{
            		node->rkey=NULL;
			node->rval=NULL;
		}
	}

	return false;
}


template <class Key, class Val>
Val* Tree<Key,Val>::remove(Key key)
{
	Node<Key,Val>* node=root;//change *root but not root
	int find=0;
	Val* returnval=NULL;
	while (find==0)
	{
		if (!node) return NULL;
		if (*(node->lkey)==key) 
		{
			find=1;
			returnval=node->lval;
		}
		else if ((node->rkey!=NULL)&&(*(node->rkey)==key)) 
		{
			find=2;
			returnval=node->rval;
		}else 
		{
			if (IsThreeNode(node)) 
			{
				if (key<*(node->lkey)) node=node->left;
				else if (key>*(node->rkey)) node=node->right;
				else node=node->center;
			}else {
				if (key<*(node->lkey)) node=node->left;
				else node=node->center;
			}
		}
	}
	Val val=*returnval;
	bool a=remove_help(root,key,val);
	if (a) {
		Node<Key,Val>* n=root;
		root=root->left;
		n->left=NULL;
		delete n;
	}
	return returnval;
}

template <class Key, class Val>
static bool insert_help(Node<Key,Val>* node, Node<Key,Val>** node1_tem, Node<Key,Val>** node2_tem, Key* &key,Val* &val)
{
	Node<Key,Val>* node1=NULL;//create node1 at this level
	Node<Key,Val>* node2=NULL;//create node2 at this level
	Node<Key,Val>* newnode=NULL;//create a new node at this level
	Node<Key,Val>* nodeposition[4];
	Key* tem_key[3];
	Val* tem_val[3];

	if (node->left!=NULL) //interior node
	{
		if (*(key)<*(node->lkey)) {//left-insert
			bool a=insert_help(node->left,&node1,&node2,key,val);
			if (a==false) return false;
			if (node->rkey!=NULL){//3-node under left-insert
				tem_key[0]=key;
				tem_key[1]=node->lkey;	
				tem_key[2]=node->rkey;
				tem_val[0]=val;
				tem_val[1]=node->lval;
				tem_val[2]=node->rval;
				nodeposition[0]=node1;
				nodeposition[1]=node2;
				nodeposition[2]=node->center;
				nodeposition[3]=node->right;
			}else {//2-node under left-insert
				node->rkey=node->lkey;
				node->rval=node->lval;
				node->lkey=key;
				node->lval=val;
				node->right=node->center;
				node->center=node2;
				node->left=node1;
				return false;
			}
		}else {//center-insert or right-insert
			if (node->rkey==NULL){ //center-insert or right-insert based on 2-node
				if (*(key)>*(node->lkey)) {//center-insert based on 2-node
					bool a=insert_help(node->center,&node1,&node2,key,val);
					if (a==false) return false;
					node->rkey=key;
					node->rval=val;
					node->center=node1;
					node->right=node2;
					return false;
					
				}
			}else {	 //center-insert or right-insert based on 3-node
				if (*(key)<*(node->rkey)) { //center-insert based on 3-node
					bool a=insert_help(node->center,&node1,&node2,key,val);
					if (a==false) return false;
					tem_key[0]=node->lkey;
					tem_key[1]=key;
					tem_key[2]=node->rkey;
					tem_val[0]=node->lval;
					tem_val[1]=val;
					tem_val[2]=node->rval;
					nodeposition[0]=node->left;
					nodeposition[1]=node1;
					nodeposition[2]=node2;
					nodeposition[3]=node->right;
				}
				if (*(key)>*(node->rkey)) {//right-insert based on 3-node
					bool a=insert_help(node->right,&node1,&node2,key,val);
					if (a==false) return false;
					tem_key[0]=node->lkey;
					tem_key[1]=node->rkey;
					tem_key[2]=key;
					tem_val[0]=node->lval;
					tem_val[1]=node->rval;
					tem_val[2]=val;
					nodeposition[0]=node->left;
					nodeposition[1]=node->center;
					nodeposition[2]=node1;
					nodeposition[3]=node2;
				}
			}
		}
	}
	else//leaf node
	{
		if (node->rkey!=NULL){	//3-node leaf
			if (*(key)<*(node->lkey)) {//left-insert
				tem_key[0]=key;
				tem_key[1]=node->lkey;	
				tem_key[2]=node->rkey;
				tem_val[0]=val;
				tem_val[1]=node->lval;
				tem_val[2]=node->rval;
				nodeposition[0]=NULL;
				nodeposition[1]=NULL;
				nodeposition[2]=NULL;
				nodeposition[3]=NULL;
			}else if (*(key)>*(node->rkey)) {//right-insert
				tem_key[0]=node->lkey;
				tem_key[1]=node->rkey;
				tem_key[2]=key;
				tem_val[0]=node->lval;
				tem_val[1]=node->rval;
				tem_val[2]=val;
				nodeposition[0]=NULL;
				nodeposition[1]=NULL;
				nodeposition[2]=NULL;
				nodeposition[3]=NULL;
			}else {//center-insert
				tem_key[0]=node->lkey;
				tem_key[1]=key;
				tem_key[2]=node->rkey;
				tem_val[0]=node->lval;
				tem_val[1]=val;
				tem_val[2]=node->rval;
				nodeposition[0]=NULL;
				nodeposition[1]=NULL;
				nodeposition[2]=NULL;
				nodeposition[3]=NULL;
			}
		}else { //2-node leaf
			if (*(key)<*(node->lkey)) {//left-insert
				node->rkey=node->lkey;
				node->rval=node->lval;
				node->lkey=key;
				node->lval=val;
			}else {//right-insert
				node->rkey=key;
				node->rval=val;
			}
			return false;
		}
	}

	//reset key and val
	key=tem_key[1];
	val=tem_val[1];

	//reset the node and newnode, and newnode is always at the right of node at same level
	node->lkey=tem_key[0];
	node->rkey=NULL;
	node->lval=tem_val[0];
	node->rval=NULL;
	node->left=nodeposition[0];
	node->center=nodeposition[1];
	node->right=NULL;
	newnode=new Node<Key,Val>;
	newnode->lkey=tem_key[2];
	newnode->rkey=NULL;
	newnode->lval=tem_val[2];
	newnode->rval=NULL;
	newnode->left=nodeposition[2];
	newnode->center=nodeposition[3];
	newnode->right=NULL;

	//reset the node1_tem and node2_tem
	*node1_tem=node;
	*node2_tem=newnode;
	return true;
}

template <class Key, class Val>
bool Tree<Key,Val>::insert(Key* key, Val* val)
{
	//Node<Key,Val>* node=root;//can directly use root
	if (isEmpty()) {
		root=new Node<Key,Val>;//should use "root" not node
		root->lkey=key;//if not pointer,should use &key
		root->lval=val;
		root->left=root->right=root->center=NULL;
		root->rkey=NULL;
		root->rval=NULL;
		return true;
	}
	Val* a=search(*key);//check if (*key) exist in the tree
	if (a!=NULL) return false;
	Node<Key,Val>* node1=NULL;
	Node<Key,Val>* node2=NULL;
	bool t=insert_help(root,&node1,&node2,key,val);
	if (t){//new node at root
		root=new Node<Key,Val>;
		root->lkey=key;//if not pointer,should use &key
		root->lval=val;
		root->rkey=NULL;
		root->rval=NULL;
		root->left=node1;
		root->center=node2;
		root->right=NULL;
	}
	return true;
}

template <class Key, class Val>
static void inOrderPrint_helper(ostream &os, Node<Key,Val>* node, int level)
{
	if (node==NULL) {
		return;
	}
	inOrderPrint_helper(os,node->left,level+1);
	for (int i=0;i<4*level;i++) 
	{
		os<<' ';
	}
	os<<*(node->lval)<<endl;
	if ((node->left==NULL)&&(node->rkey!=NULL))
	{
		for (int i=0;i<4*level;i++) 
		{
			os<<' ';
		}
		os<<*(node->rval)<<endl;
	}
	inOrderPrint_helper(os,node->center,level+1);
	if (node->right!=NULL) {
		for (int i=0;i<4*level;i++) 
		{
			os<<' ';
		}
		os<<*(node->rval)<<endl;
		inOrderPrint_helper(os,node->right,level+1);
	}
}

template <class Key, class Val>
void Tree<Key,Val>::inOrderPrint(ostream &os) const
{
	inOrderPrint_helper(os,root,0);
}

template <class Key, class Val>
Tree<Key,Val>::Tree()
{
	root=NULL;
}

template <class Key, class Val>
Tree<Key,Val>::Tree(const Tree &t)
{
	root=new Node<Key,Val>;
	copytreenode(root,t->root);//
}

template <class Key, class Val>
Tree<Key,Val>& Tree<Key,Val>::operator=(const Tree &t)
{
	removetreenode(root);
	copytreenode(root,t->root);//
	return *this;
}

template <class Key, class Val>
Tree<Key,Val>::~Tree()
{
	removetreenode(root);
	delete root;
}

/*
This is an another method of insert, the coding thought is correct but I don't debug it

template <class Key, class Val>
static void addnode(Node<Key,Val>* x, Node<Key,Val>* cur, Node<Key,Val>* helper, Key* temkey,Val* temval)//how to??
{
	if ((cur->left==NULL)&&(cur->center==NULL)&&(cur->right==NULL))
	{
		if (cur->rkey==NULL) {//2-node leaf
			if (*(x->lkey)<*(cur->lkey)) {
				cur->rkey=cur->lkey;
				cur->rval=cur->lval;
				cur->lkey=x->lkey;
				cur->lval=x->lval;
			}else {
				cur->rkey=x->lkey;
				cur->rval=x->lval;
			}
			delete x;
			helper=NULL;
		}else {//3-node leaf
			if (*(x->lkey)<*(cur->lkey)) {
				temkey=cur->lkey;
				temval=cur->lval;
				Node<Key,Val>* tem=x;//can??
				x=cur;
				cur=tem;
			}else if(*(x->lkey)>*(cur->rkey)) {
				temkey=cur->rkey;
				temval=cur->rval;
			}else {
				temkey=x->lkey;
				temval=x->lval;
			} 
			helper=x;
		}
		return;
	}
	if (*(x->lkey)<*(cur->lkey)) {
		child=1;
		cur_next=cur->left;
	}else if (*(x->lkey)<*(cur->rkey)||((cur->rkey==NULL)&&(cur->right==NULL))) {
		child=2;
		cur_next=cur->center;
	}else {
		child=3;
		cur_next=cur->right;
	}
	int child;
	Node<Key,Val>* cur_next=NULL;
	Node<Key,Val>* helper_next=NULL;
	Key* temkey_next=NULL;//???/can????and many &???????
	Val* temval_next=NULL;
	addnode(x, &cur_next, &helper_next, &temkey_next, &temval_next);//???????????????
	if (helper_next!=NULL) {//not 2-node at leaf
		if (cur->rkey==NULL) {//2-node at interior
			if (child==1) {
				cur->right=cur->center;
				cur->center=helper_next;
				cur->left=cur_next;
				cur->rval=cur->lval;
				cur->rkey=cur->lkey;
				cur->lval=temkey_next;
				cur->lkey=temval_next;
			}else {//child==2
				cur->right=helper_next;
				cur->center=cur->next;
				cur->rkey=temkey_next;
				cur->rval=temval_next;
			}
		}
		else {//3-node at interior
			helper=new Node<Key,Val>;//new pointer???????when use"->"
			helper->lkey=NULL;//if not pointer,should use &key??
			helper->lval=NULL;
			helper->left=x->right=x->center=NULL;
			helper->rkey=NULL;
			helper->rval=NULL;
			if (child==1) {
				helper->center=cur->right;
				helper->left=cur->center;
				cur->left=cur_next;
				cur->center=helper_next;
				cur->right=NULL;
				helper->lkey=cur->rkey;
				helper->lval=cur->rval;
				temkey=cur->lkey;
				temval=cur->lval;
				cur->lkey=temkey_next;
				cur->lval=temval_next;
				cur->rval=NULL;
				cur->rkey=NULL;
			}else if (child==2) {
				helper->left=helper_next;
				helper->center=cur->right;
				cur->right=NULL;
				cur->center=cur_next;
				temkey=temkey_next;
				temval=temval_next;
				helper->lkey=cur->lkey;
				helper->lval=cur->rval;
				cur->rkey=NULL;
				cur->rval=NULL;
			}else {
				helper->left=cur_next;
				helper->center=helper_next;
				cur->right=NULL;
				helper->lkey=temkey_next;
				helper->lval=temval_next;
				temkey=cur->rkey;
				temval=cur->rval;
				cur->rkey=NULL;
				cur->rval=NULL;	
			}
		}
		
	}
}

template <class Key, class Val>
bool Tree<Key,Val>::insert(Key* key, Val* val);
{
	Node<Key,Val>* node=root;//can directly use root
	if (isEmpty()) {
		root=new Node<Key,Val>;//should use "root" not node
		root->lkey=key;//if not pointer,should use &key
		root->lval=val;
		root->left=root->right=root->center=NULL;
		root->rkey=NULL;
		root->rval=NULL;
		return true;
	}
	Val* a=search_help(node,key);//node don't change but *node change
	if (a!=NULL) return false;
	Key* temkey;
	Val* temval; 
	Node<Key,Val> helper=NULL;
	Node<Key,Val>* x=new Node<Key,Val>;
	x->lkey=key;
	x->lval=val;
	x->left=x->right=x->center=NULL;
	x->rkey=NULL;
	x->rval=NULL;
	addnode(x, &node, &helper, &temkey, &temval);//right??
	if (helper==NULL) {
		Node<Key,Val>* newhead=new Node<Key,Val>;
		newhead->lkey=temkey;
		newhead->lval=temval;
		newhead->rkey=NULL;
		newhead->rval=NULL;
		newhead->left=helper;
		newhead->center=helper;
		newhead->right=NULL;
		root=newhead;
	}
	return true;
}
*/


#endif /*__TWO-THREE-TREE_H__*/
