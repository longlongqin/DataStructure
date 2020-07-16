#ifndef DSCAPP_BINTREE_STATEJUDGE_H
#define DSCAPP_BINTREE_STATEJUDEG_H

/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x)		(!(x.parent_))	//判断是否为根节点
#define IsLChild(x)		(!IsRoot(x) && (&(x) == (x).parent->lc_))
#define IsRChild(x)		(!IsRoot(x) && (&(x) == (x).parent->rc_))
#define HasParent(x)	(!IsRoot(x))
#define HasLChild(x)	(x.lc_)
#define HasRChild(x)	(x.rc_)
#define HasChild(x)		(x.lc_ || x.rc_)
#define HasBothChild(x)	(x.lc_ && x.rc_)
#define IsLeaf(x)		(!HasChild(x))

 /******************************************************************************************
 * 与BinNode具有特定关系的节点及指针
 ******************************************************************************************/

//兄弟
#define sibling(p)	\
	(IsLChild(*(p))? (p).parent_->rc_ :(p).parent_->lc_)

//叔叔
#define uncle(x)	\
	(IsLChild( *((x)->parent_) ) ? (x)->parent_->parent_->rc_ : (x)->parent_->parent_->lc_ )

//来自父亲的引用
#define FromParentTo(x)	\
	(IsRoot(x) ? root_ : ((IsLChild(x) ? x.parent_->rc_ : x.parent_->lc_))


#endif
