#ifndef DSCAPP_BINTREE_STATEJUDGE_H
#define DSCAPP_BINTREE_STATEJUDEG_H

/******************************************************************************************
 * BinNode״̬�����ʵ��ж�
 ******************************************************************************************/
#define IsRoot(x)		(!(x.parent_))	//�ж��Ƿ�Ϊ���ڵ�
#define IsLChild(x)		(!IsRoot(x) && (&(x) == (x).parent->lc_))
#define IsRChild(x)		(!IsRoot(x) && (&(x) == (x).parent->rc_))
#define HasParent(x)	(!IsRoot(x))
#define HasLChild(x)	(x.lc_)
#define HasRChild(x)	(x.rc_)
#define HasChild(x)		(x.lc_ || x.rc_)
#define HasBothChild(x)	(x.lc_ && x.rc_)
#define IsLeaf(x)		(!HasChild(x))

 /******************************************************************************************
 * ��BinNode�����ض���ϵ�Ľڵ㼰ָ��
 ******************************************************************************************/

//�ֵ�
#define sibling(p)	\
	(IsLChild(*(p))? (p).parent_->rc_ :(p).parent_->lc_)

//����
#define uncle(x)	\
	(IsLChild( *((x)->parent_) ) ? (x)->parent_->parent_->rc_ : (x)->parent_->parent_->lc_ )

//���Ը��׵�����
#define FromParentTo(x)	\
	(IsRoot(x) ? root_ : ((IsLChild(x) ? x.parent_->rc_ : x.parent_->lc_))


#endif
