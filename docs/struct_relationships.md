# MiniRT Struct Relationships

```mermaid
classDiagram
    class t_f_node {
        char val
        t_f_node* next
    }

    class t_p_node {
        char* str
        t_p_node* next
    }

    class t_vect {
        float x
        float y
        float z
    }

    class t_ray {
        t_vect origin
        t_vect direction
    }

    class t_hit_record {
        t_vect point
        t_vect normal
        double t
    }

    class t_intersect_info {
        t_hit_record hit
        uint32_t color
    }

    class t_sphere_collision {
        double closest_t
        t_sphere* closest_sphere
    }

    class t_plane_collision {
        double closest_t
        t_plane* closest_plane
    }

    class t_cylinder_collision {
        double closest_t
        t_cylinder* closest_cylinder
    }

    class t_cone_collision {
        double closest_t
        t_cone* closest_cone
    }

    class t_material {
        double amb
        double diff
        double spec
        double shin
        double refl
    }

    class t_texture {
        t_texture_type type
        double scale
        uint32_t pri_color
        uint32_t sec_color
        void* texture_data
        int width
        int height
    }

    class t_bump_map {
        bool enabled
        void* map
        int width
        int height
    }

    class t_obj_pro {
        t_material mat
        t_texture txm
        t_bump_map bpm
    }

    class t_img {
        void* img_ptr
        char* pixels_ptr
        int bpp
        int endian
        int line_len
    }

    class t_amb {
        double ratio
        uint32_t rgb
        bool set
    }

    class t_cam {
        t_vect norm
        t_vect cord
        double fov
        bool set
    }

    class t_light {
        t_vect cord
        double ratio
        uint32_t color
        t_light* next
    }

    class t_sphere {
        t_vect cord
        double diameter
        t_obj_pro pro
        t_sphere* next
    }

    class t_plane {
        t_vect norm
        t_vect cord
        double radius
        t_obj_pro pro
        t_plane* next
    }

    class t_cylinder {
        t_vect cord
        t_vect norm
        double diameter
        double height
        t_obj_pro pro
        t_cylinder* next
    }

    class t_cone {
        t_vect cord
        t_vect norm
        double height
        double diameter
        t_obj_pro pro
        t_cone* next
    }

    class t_master {
        void* mlx_ptr
        void* win_ptr
        t_img img
        t_amb amb_head
        t_cam cam_head
        t_light* light_head
        t_sphere* sphere_head
        t_plane* plane_head
        t_cylinder* cylinder_head
        t_cone* cone_head
    }

    t_f_node --> t_f_node : next
    t_p_node --> t_p_node : next

    t_ray --> t_vect
    t_hit_record --> t_vect
    t_intersect_info --> t_hit_record

    t_sphere_collision --> t_sphere
    t_plane_collision --> t_plane
    t_cylinder_collision --> t_cylinder
    t_cone_collision --> t_cone

    t_obj_pro --> t_material
    t_obj_pro --> t_texture
    t_obj_pro --> t_bump_map

    t_cam --> t_vect
    t_light --> t_vect
    t_light --> t_light : next

    t_sphere --> t_vect
    t_sphere --> t_obj_pro
    t_sphere --> t_sphere : next

    t_plane --> t_vect
    t_plane --> t_obj_pro
    t_plane --> t_plane : next

    t_cylinder --> t_vect
    t_cylinder --> t_obj_pro
    t_cylinder --> t_cylinder : next

    t_cone --> t_vect
    t_cone --> t_obj_pro
    t_cone --> t_cone : next

    t_master --> t_img
    t_master --> t_amb
    t_master --> t_cam
    t_master --> t_light
    t_master --> t_sphere
    t_master --> t_plane
    t_master --> t_cylinder
    t_master --> t_cone
