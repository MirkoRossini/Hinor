#include "char_trie.h"


#define INITIAL_RESP_SIZE 512
#define INITIAL_TEMP_STRING_SIZE 100

Trie *init_trie(void)
{
    Trie *trie = (Trie *)malloc(sizeof(Trie));
    trie->root = NULL;
    trie->options = NULL;
    //tree->pre_allocd_response = NULL;
    return trie;
}
TrieNode *init_node(void)
{
       TrieNode *n = (TrieNode *)malloc(sizeof(TrieNode));
       n->ch = '\0';
       n->word_end = 0;
       n->value = NULL;
       n->center = NULL;
       n->right = NULL;
       n->left = NULL;
       return n;
}

struct temp_string {
    char *s; //String
    int length; //Current length of the string
    int max; //Max length of the string
};

struct temp_string *init_temp_string(void)
{
    struct temp_string *t = (struct temp_string*)malloc(sizeof(struct temp_string));
    t->length = 0;
    t->s = malloc(INITIAL_TEMP_STRING_SIZE);
    strcpy(t->s,"");
    t->max = INITIAL_TEMP_STRING_SIZE;
    return t;
}

void  free_temp_string(struct temp_string *temp_str)
{
    if(temp_str == NULL)
        return;
    free(temp_str->s);
    free(temp_str);
}

void free_response(AutoCompResponse *resp)
{

    if(resp == NULL)
        return;
    free(resp->resp_string);
    free(resp);

}
void free_node(TrieNode *node)
{
    if(node == NULL)
        return;
    free(node->value);
    free(node);
}
void rec_free_trie(TrieNode *node)
{
    if(node == NULL)
        return;
    rec_free_trie(node->left);
    rec_free_trie(node->center);
    rec_free_trie(node->right);
    free_node(node);
}

int count_nodes(TrieNode *node)
{
    if(node == NULL)
        return 0;
    return 1 + count_nodes((TrieNode*)node->left) + \
                 count_nodes(node->center) + \
                 count_nodes(node->right);
}
int count_memory(TrieNode *node)
{
    if(node == NULL)
        return 0;
    int plus = 0;
    if (node->value!=NULL)
        plus = strlen(node->value);

    return sizeof(*node) + plus + count_memory((TrieNode*)node->left) + \
                 count_memory(node->center) + \
                 count_memory(node->right);
}
int count_empty_pointers(TrieNode *node)
{
    if(node == NULL)
        return 1;
    return 0 + count_empty_pointers((TrieNode*)node->left) + \
                        count_empty_pointers(node->center) + \
                        count_empty_pointers(node->right);
}
void free_trie(Trie *trie)
{
    if(trie == NULL)
        return;
    if(trie->root == NULL)
        return;
    rec_free_trie(trie->root);
    //free_response(tree->pre_allocd_response);
    free(trie);
}

void err_if(int expr,const char *msg)
{
    if(!expr)
    {
        perror(msg);
    }

}

QueryOptions *init_query_options(void)
{
    QueryOptions *qo=malloc(sizeof(QueryOptions));
    qo->max_strings = 10;
    return qo;
}
void free_query_options(QueryOptions *qo)
{
    free(qo);
}

void add_in_tree(char * s, int pos, TrieNode **node,char *value)
{
    //printf("deb\n");
    if ((*node) == NULL) 
    {
       (*node) = init_node();
       (*node)->ch = s[pos];
    }
    if (s[pos] < (*node)->ch) { add_in_tree(s, pos, &((*node)->left), value); }
    else if (s[pos] > (*node)->ch) { add_in_tree(s, pos, &((*node)->right), value); }
    else
    {
        if (s[pos + 1] == '\0' || s[pos + 1] == '\n' || s[pos + 1] == '\r') 
        {
            (*node)->word_end = 1;
            if(value != NULL)
            {
                free((*node)->value);
                (*node)->value = (char *)malloc(strlen(value) + 1);
                if(!(*node)->value)
                {
                    perror("ERROR allocating node value in add_in_tree");
                    return;
                }
                else
                {
                    strcpy((*node)->value,value);
                }
            }
            else
            {   
                free((*node)->value);
            }
        }
        else { add_in_tree(s, pos + 1, &((*node)->center), value); }
    }
}

void add(Trie *tree,char *s)
{
    err_if(!(s == NULL || strcmp(s,"")==0),"Bad argument");
    add_in_tree(s, 0, &tree->root,NULL);
}
void add_value(Trie *tree,char *s,char *value)
{
    err_if(!(s == NULL || strcmp(s,"")==0),"Bad argument");
    add_in_tree(s, 0, &tree->root,value);
}

TrieNode *last_node(Trie *tree, char *s)
{
    int pos = 0;
    TrieNode *node = tree->root;
    while (node != NULL)
    {
        int cmp = s[pos] - node->ch;
        if (cmp < 0) { node = node->left; }
        else if (cmp > 0) { node = node->right; }
        else
        {
            pos++;
            if (s[pos] == '\0')
            {
                return node;
            }
            node = node->center;
        }
    }
    return NULL;
}

int contains(Trie *tree,char *s)
{
    err_if(!(s == NULL || (strcmp(s , "")==0)),"BadArgument");
    TrieNode *last = last_node(tree,s);
    if(last!=NULL) return last->word_end;
    else return 0;
}

char *get(Trie *tree,char *s)
{
    err_if(!(s == NULL || (strcmp(s ,"") == 0)),"BadArgument");
    TrieNode *last = last_node(tree,s);
    if(last!=NULL && last->word_end)
    {
            return last->value;
    }
    else
       return NULL;
}
AutoCompResponse *init_autocomp_response(void)
{

    AutoCompResponse *resp = (AutoCompResponse *) malloc(sizeof(AutoCompResponse));
    if(!resp)
    {
        perror("Error allocating AutoCompResponse");
    }
    resp->max_size = INITIAL_RESP_SIZE;
    resp->num_strings = 0;
    resp->curr_size = 0;
    resp->resp_string = (char *) malloc(resp->max_size);
    if(!resp->resp_string)
    {
        perror("Error allocating resp_string");
    }

    strcpy(resp->resp_string,"");
    return resp;
}


int add_string(AutoCompResponse *base,char *initial_string, char *to_add,int len,TrieNode *node)
{
    int initial_string_len = strlen(initial_string);
    int value_len = 0;
    if(node->value != NULL)
        value_len = strlen(node->value);
    if((node->value != NULL && (base->curr_size + len + 2 + initial_string_len + value_len) > base->max_size) ||\
        (base->curr_size + len + 1 + initial_string_len) > base->max_size)
    {
        if(!(base->resp_string = realloc(base->resp_string,base->max_size * 2)))
        {
            perror("NO REALLOC");
            return 0;
        }
        base->max_size = base->max_size * 2;
    }
    strncat(base->resp_string, initial_string,initial_string_len);
    strncat(base->resp_string, to_add,len);
    if(node->value != NULL)
        strncat(base->resp_string,":",1);
        strncat(base->resp_string,node->value,value_len);
    strncat(base->resp_string,",",1);
    base->curr_size = base->curr_size + len + initial_string_len + 1;
    if(node->value != NULL)
        base->curr_size = base->curr_size + value_len + 1;
    base->num_strings = base->num_strings + 1;
    return 0;
}

int add_to_temp_string(struct temp_string *ts,char c,int where)
{
    if(where >= (ts->max - 1))
    {
        ts->s = realloc(ts->s,ts->max*2);
        ts->max = ts->max*2;
    }
    if(where > ts->length)
        ts->length = where;
    ts->s[where] = c;
    ts->s[where + 1] = '\0';
    return 0;
}
void recursive_visit_strings(TrieNode *curr,AutoCompResponse *ret,QueryOptions *qo,char * initial_string,struct temp_string *curr_string, int len_curr_string)
{
    if(ret->num_strings == qo->max_strings)
        return;

    if(curr == NULL)
    {
        return;
    }
    recursive_visit_strings(curr->left,ret,qo,initial_string,curr_string,len_curr_string);
    add_to_temp_string(curr_string,curr->ch,len_curr_string);
    if(curr->word_end)
    {
        add_string(ret,initial_string,curr_string->s,len_curr_string+1,curr);
    }
    recursive_visit_strings(curr->center,ret,qo,initial_string,curr_string,len_curr_string + 1);
    recursive_visit_strings(curr->right,ret,qo,initial_string,curr_string,len_curr_string);
    return;
}


AutoCompResponse *autocomp(Trie *tree,char *s)
{
    return autocomp_limit(tree,s,10);
}


AutoCompResponse *autocomp_limit(Trie *tree,char *s,int limit)
{
    /*if(tree->pre_allocd_response == NULL)
        tree->pre_allocd_response = init_autocomp_response();
    tree->pre_allocd_response->resp_string[0] = '\0';
    tree->pre_allocd_response->curr_size = 0;*/
    AutoCompResponse *ret = init_autocomp_response();
    QueryOptions *qo = init_query_options();
    qo->max_strings = limit;
    TrieNode *last = last_node(tree,s);
    struct temp_string *temp_str = init_temp_string();
    if(last != NULL)
    {
        if(last->word_end)
        {
            add_string(ret,s,"",0,last);
        }
        recursive_visit_strings(last->center,ret,qo,s,temp_str,0);
    }
    free_temp_string(temp_str);
    free_query_options(qo);
    return ret;
}

