#include "m_pd.h"

#define MAX_LIST_SIZE 256

////////////////////////////////////////////////////////////////////////////////
// Data
//

// State variables in a struct 
typedef struct edit_distance {

   t_object x_obj;
   t_outlet *outlet;
   t_inlet *inlet_right;

   float list_right[MAX_LIST_SIZE];
   int list_right_length;

} t_edit_distance;

// A pointer to the class object.
static t_class *edit_distance_class;

////////////////////////////////////////////////////////////////////////////////
// Methods
// 

// Received a list on left inlet. Calculate distance and output float
static void edit_distance_left(t_edit_distance *x, t_symbol *s, int argc, t_atom *argv) {
   // Get floats in inlet list;
   int i;
   int list_left_length = argc;
   float list_left[MAX_LIST_SIZE];
   for(i=0; i<argc; i++){
      list_left[i] = atom_getfloatarg(i, argc, argv);
   }

   // Do whatever with list_left[], x->list_right[], list_left_length, x->list_right_length
   post("%f", list_left[0]);
   post("%f", x->list_right[0]);

   outlet_float(x->outlet, 1.0);
}

// Received a list on right inlet. Store it on x->list_right
static void edit_distance_right(t_edit_distance *x, t_symbol*s, int argc, t_atom*argv) {
   x->list_right_length = argc;

   // Get floats in inlet list;
   int i;
   for(i=0; i<argc; i++){
      x->list_right[i] = atom_getfloatarg(i, argc, argv);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Constructor, destructor
//
static void *edit_distance_new(void) {
   t_edit_distance *x = (t_edit_distance *)pd_new(edit_distance_class);
   x->inlet_right=inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("list"), gensym("lst2"));
   x->outlet = outlet_new(&x->x_obj, &s_anything);
   post("edit_distance_new");
   return (void *)x;
}

static void edit_distance_free(t_edit_distance *x)
{ 
  /* if(x->x_length) { */
  /*        freebytes(x->x_length, x->x_lcount*sizeof(int)); */
  /*            x->x_length=0; */
  /*                x->x_lcount=0; */
  /*                  } */
  /*   inlet_free(x->x_lengin); */
   post("freeing");

}

///////////////////////////////////////////////////////////////////////////////
// Class definition
// 
void edit_distance_setup(void) {
   post("edit_distance_setup");
   edit_distance_class = class_new(gensym("edit_distance"), (t_newmethod)edit_distance_new, (t_method)edit_distance_free, sizeof(t_edit_distance), 0, 0);
   class_addlist(edit_distance_class, edit_distance_left);
   class_addmethod(edit_distance_class, (t_method)edit_distance_right, gensym("lst2"), A_GIMME, 0);
}

