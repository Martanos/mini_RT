#include "../include/mini_rt.h"
#include "libvect.h"

void set_face_normal(t_hit_record *rec, const t_ray *r,
        const t_vect *outward_normal)
{
    if (ft_vect_dot(r->direction, *outward_normal) > 0.0)
        rec->normal = ft_vect_mul_all(*outward_normal, -1); // Inside
    else
        rec->normal = *outward_normal; // Outside
}
