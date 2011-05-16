struct unode{
	struct rb_node __rb_node;
	int __num;      //this is to record our data.
};

struct unode * rb_search_unode( struct rb_root * root , int target ){

       struct rb_node * n = root->rb_node;
       struct unode * ans;

       while( n ){
              //Get the parent struct to obtain the data for comparison
              ans = rb_entry( n , struct unode , __rb_node );

              if( target < ans->__num )
                     n = n->rb_left;
              else if( target > ans->__num )
                     n = n->rb_right;
              else
                     return ans;

       }
       return NULL;

}


struct unode * rb_insert_unode( struct rb_root * root , int target , struct rb_node * source ){

       struct rb_node **p = &root->rb_node;
       struct rb_node *parent = NULL;
       struct unode * ans;

       while( *p ){

              parent = *p;
              ans = rb_entry( parent , struct unode , __rb_node );

              if( target < ans->__num )
                     p = &(*p)->rb_left;
              else if( target > ans->__num )
                     p = &(*p)->rb_right;
              else
                     return ans;

       }
       rb_link_node( source , parent , p );             //Insert this new node as a red leaf.
       rb_insert_color( source , root );           //Rebalance the tree, finish inserting
       return NULL;

}



void rb_erase_unode( struct rb_node * source , struct rb_root * root ){

       struct unode * target;
      
       target = rb_entry( source , struct unode , __rb_node );
       rb_erase( source , root );                           //Erase the node
       free( target );                                     //Free the memory

}

struct rb_root root = RB_ROOT;
struct unode * node;

node = ( struct unode * )malloc( sizeof( struct unode ) );
rb_insert_unode( &root , op , &node->__rb_node );

if the number “op” already exists then free the memory:
free( node );
else record the “op”
node->__num = op;

To search:

rb_search_unode( &root , op );

To delete:

First find the node
node = rb_search_unode( &root , op );
if node is not null then erase the node
rb_erase_unode( &node->__rb_node , &root );
