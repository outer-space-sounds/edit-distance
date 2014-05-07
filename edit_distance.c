#include "m_pd.h"

////////////////////////////////////////////////////////////////////////////////
// Data
//

// State variables in a struct 
typedef struct edit_distance {
   t_object x_obj;
   t_outlet *outlet;
   t_inlet *inlet_right;
} t_edit_distance;

// A pointer to the class object.
t_class *edit_distance_class;

////////////////////////////////////////////////////////////////////////////////
// Methods
// 

// Received a list on left inlet
static void edit_distance_left(t_edit_distance *x, t_symbol *s, int argc, t_atom *argv) {
   post("List on left");

   outlet_float(x->outlet, 1.0);

  /* int i; */
  /*  */
  /* if(x->x_lcount<1) { */
  /*   outlet_anything(x->x_obj.ob_outlet, s, argc, argv); */
  /*   return; */
  /* } */

  /* for(i=0; i<x->x_lcount; i++) { */
  /*   int len=x->x_length[i]; */
  /*   if(len>argc) { */
  /*     list2lists_output(x, argc, argv); */
  /*     return; */
  /*   } */
  /*   list2lists_output(x, len, argv); */
  /*   argv+=len; */
  /*   argc-=len; */
  /* } */

   
}

// Received a list on right inlet
static void edit_distance_right(t_edit_distance *x, t_symbol*s, int argc, t_atom*argv) {
   post("List on right");
  /* if(x->x_length!=0) { */
  /*   freebytes(x->x_length, sizeof(t_atom)*x->x_lcount); */
  /* } */
  /* x->x_lcount=0; */
  /* x->x_length=0; */

  /* DEBUGFUN(post("list of length %d", argc)); */

  /* if(argc>0) { */
  /*   int i; */
  /*   x->x_lcount=argc; */
  /*   x->x_length=(t_int*)getbytes((x->x_lcount)*sizeof(t_int)); */
  /*   for(i=0; i<argc; i++) { */
  /*     int index=atom_getint(argv+i); */
  /*     if(index<0) { */
	/* pd_error(x, "[list2lists]: clamped negative index=%d to 0!", index); */
	/* index=0; */
  /*     } */
  /*     x->x_length[i]=index; */
  /*   } */
  /* } */

  /* DEBUGFUN(post("list2: %d %x", x->x_lcount, x->x_length)); */
}

void edit_distance_float(t_edit_distance *x, t_floatarg f) {
   post("edit_distance: %f", f);
   (void)x;
}

// Received the message "rats"
void edit_distance_rats(t_edit_distance *x) {
   post("edit_distance: rats");
   (void)x;
}


///////////////////////////////////////////////////////////////////////////////
// Constructor
//
void *edit_distance_new(void) {
   t_edit_distance *x = (t_edit_distance *)pd_new(edit_distance_class);
   x->inlet_right=inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("list"), gensym("lst2"));
   x->outlet = outlet_new(&x->x_obj, &s_anything);
   post("edit_distance_new");
   return (void *)x;
}

///////////////////////////////////////////////////////////////////////////////
// Class definition
// 
void edit_distance_setup(void) {
   post("edit_distance_setup");
   edit_distance_class = class_new(gensym("edit_distance"), (t_newmethod)edit_distance_new, 0, sizeof(t_edit_distance), 0, 0);
   class_addlist(edit_distance_class, edit_distance_left);
   class_addmethod(edit_distance_class, (t_method)edit_distance_right, gensym("lst2"), A_GIMME, 0);
}

