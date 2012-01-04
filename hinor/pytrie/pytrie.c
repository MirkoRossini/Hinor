/* Example of embedding Python in another program */

#include "Python.h"
#include "pytrie.h"

void inithinor(void); /* Forward */

int main(int argc, char **argv)
{
    /* Pass argv[0] to the Python interpreter */
    //Py_SetProgramName(argv[0]);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Add a static module */
    inithinor();


    /*PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("print sys.builtin_module_names\n");
    PyRun_SimpleString("print sys.modules.keys()\n");
    PyRun_SimpleString("print sys.executable\n");
    PyRun_SimpleString("print sys.argv\n");
    */
    /* Note that you can call any public function of the Python
       interpreter here, e.g. call_object(). */

    /* Some more application specific code */
    //printf("\nGoodbye, cruel world\n");

    /* Exit, cleaning up the interpreter */
    Py_Exit(0);
    return 0;
    /*NOTREACHED*/
}

/* A static module */


static int CharTrie_init(CharTrie *self, PyObject *args, PyObject *kwds)
{
    self->trie = init_trie();
    return 0;
}

static void CharTrie_dealloc(CharTrie *self)
{
    free_trie(self->trie);
        //Py_XDECREF(self->dict);
    self->ob_type->tp_free((PyObject *)self);
}


static PyObject *
CharTrie_add(CharTrie *self, PyObject *args)
{
    char *key;
    char *value = NULL;
    if (!PyArg_ParseTuple(args, "s|s", &key,&value)) 
    {
        return NULL;
    }
    if(value)
        add_value(self->trie, key, value);
    else
        add(self->trie,key);
    Py_INCREF(Py_None);
    return Py_None;;
}
static PyObject *
CharTrie_get(CharTrie *self, PyObject *args)
{

    //printf("%d \n", count_nodes(self->trie->root));
    char *key;
    if (!PyArg_ParseTuple(args, "s", &key)) 
    {
        return NULL;
    }
    char *r = get(self->trie, key);
    if(r == NULL)
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    else
    {
        return PyString_FromString(r);
    }
}

static PyObject *
CharTrie_autocomp(CharTrie *self, PyObject *args)
{
    char *key;
    if (!PyArg_ParseTuple(args, "s", &key)) 
    {
        return NULL;
    }
    char *r = autocomp(self->trie, key)->resp_string;
    if(r == NULL)
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    else
    {
        return PyString_FromString(r);
    }
}

static PyMethodDef CharTrie_methods[] =
{
    {
        "add",(PyCFunction) CharTrie_add,METH_VARARGS,
        "Adds a key to the chartrie. You can add a simple \
         key with add(key) or a key with an associated value with add(key,value)"
    },
    {
        "get",(PyCFunction) CharTrie_get,METH_VARARGS,
        "Returns the value associated with the given key. \
         Returns None if the key is not in the trie. \
         returns None if the key hasn't any value associated with it"
    },
    {
        "autocomp",(PyCFunction) CharTrie_autocomp,METH_VARARGS,
        "Returns a string containing all the strings \
         in the trie that begin with the given key "
    },
    {NULL, NULL}           /* sentinel */
};



static PyTypeObject
CharTrieType = {
   PyObject_HEAD_INIT(NULL)
   0,                         /* ob_size */
   "CharTrie",               /* tp_name */
   sizeof(CharTrie),         /* tp_basicsize */
   0,                         /* tp_itemsize */
   (destructor)CharTrie_dealloc, /* tp_dealloc */
   0,                         /* tp_print */
   0,                         /* tp_getattr */
   0,                         /* tp_setattr */
   0,                         /* tp_compare */
   0,                         /* tp_repr */
   0,                         /* tp_as_number */
   0,                         /* tp_as_sequence */
   0,                         /* tp_as_mapping */
   0,                         /* tp_hash */
   0,                         /* tp_call */
   0,                         /* tp_str */
   0,                         /* tp_getattro */
   0,                         /* tp_setattro */
   0,                         /* tp_as_buffer */
   Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags*/
   "CharTrie object. Autocompletion data structure.",        /* tp_doc */
   0,                         /* tp_traverse */
   0,                         /* tp_clear */
   0,                         /* tp_richcompare */
   0,                         /* tp_weaklistoffset */
   0,                         /* tp_iter */
   0,                         /* tp_iternext */
   CharTrie_methods,         /* tp_methods */
   //CharTrie_members,         /* tp_members */
   0,         /* tp_members */
   0,                         /* tp_getset */
   0,                         /* tp_base */
   0,                         /* tp_dict */
   0,                         /* tp_descr_get */
   0,                         /* tp_descr_set */
   0,                         /* tp_dictoffset */
   (initproc)CharTrie_init,  /* tp_init */
   0,                         /* tp_alloc */
   0,                         /* tp_new */
};



void
inithinor(void)
{
    PyObject *mod;
    PyImport_AddModule("hinor");
    mod = Py_InitModule("hinor",NULL);
    if(!mod)
        return;
    CharTrieType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&CharTrieType) < 0) 
        return;
    Py_INCREF(&CharTrieType);
    PyModule_AddObject(mod, "CharTrie", (PyObject*)&CharTrieType);
}
