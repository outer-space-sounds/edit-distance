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

static int min(int a, int b, int c){
   int temp;
   if(a<b){
      temp = a;
   }
   else{
      temp = b;
   }

   int min;
   if(temp<c){
      min = temp; 
   }
   else{
      min = c; 
   }

   return min;
}

// Received a list on left inlet. Calculate distance and output float
static void edit_distance_left(t_edit_distance* x, t_symbol* s, int argc, t_atom* argv) {
   (void)s;

   // Get floats in inlet list;
   int i,j;
   int list_left_length = argc;
   float list_left[MAX_LIST_SIZE];
   for(i=0; i<argc; i++){
      list_left[i] = atom_getfloatarg(i, argc, argv);
   }

   /////////////////////////////
   // HERE WE GO
   /////////////////////////////
   int matrix[list_left_length + 1][x->list_right_length + 1];

   // Clear mtx
   for(j=0; j<=x->list_right_length; j++){
      for(i=0; i<=list_left_length; i++){
         matrix[i][j] = 0;
      }
   }

   for(j=1; j<=x->list_right_length; j++){
      matrix[0][j] = j; 
   }

   for(i=1; i<=list_left_length; i++){
      matrix[i][0] = i; 
   }

   for(j=1; j<=x->list_right_length; j++){
      for(i=1; i<=list_left_length; i++){
         if(list_left[i-1] == x->list_right[j-1]){
            matrix[i][j] = matrix[i-1][j-1];
         }
         else{
            matrix[i][j] = min(matrix[i-1][j]+1, matrix[i][j-1]+1, matrix[i-1][j-1]+1);
         }
      }
   }

   // Debug
   /* for(j=0; j<=x->list_right_length; j++){ */
   /*    for(i=0; i<=list_left_length; i++){ */
   /*       post("%i, %i: %i",i,j,matrix[i][j]); */
   /*    } */
   /* } */

   float result = (int)matrix[list_left_length][x->list_right_length];
   outlet_float(x->outlet, result);
}

// Received a list on right inlet. Store it on x->list_right
static void edit_distance_right(t_edit_distance* x, t_symbol* s, int argc, t_atom* argv) {
   (void)s;

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
   return (void *)x;
}

static void edit_distance_free(t_edit_distance *x) { 
   (void)x;
}

///////////////////////////////////////////////////////////////////////////////
// Class definition
// 
void edit_distance_setup(void) {
   edit_distance_class = class_new(gensym("edit_distance"), (t_newmethod)edit_distance_new, (t_method)edit_distance_free, sizeof(t_edit_distance), 0, 0);
   class_addlist(edit_distance_class, edit_distance_left);
   class_addmethod(edit_distance_class, (t_method)edit_distance_right, gensym("lst2"), A_GIMME, 0);
}

