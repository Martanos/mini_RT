/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malee <malee@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:13:57 by malee             #+#    #+#             */
/*   Updated: 2025/02/06 15:47:49 by malee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_print_texture(t_texture *texture)
{
	printf(GREEN "Texture type: %d\n" RESET, texture->type);
	printf(GREEN "Texture scale: %f\n" RESET, texture->scale);
	printf(GREEN "Texture primary color: %d %d %d\n" RESET,
		ft_get_r(texture->pri_color), ft_get_g(texture->pri_color),
		ft_get_b(texture->pri_color));
	printf(GREEN "Texture secondary color: %d %d %d\n" RESET,
		ft_get_r(texture->sec_color), ft_get_g(texture->sec_color),
		ft_get_b(texture->sec_color));
}

static void	ft_print_material(t_material *material)
{
	printf(GREEN "Material ambient: %f\n" RESET, material->amb);
	printf(GREEN "Material diffuse: %f\n" RESET, material->diff);
	printf(GREEN "Material specular: %f\n" RESET, material->spec);
	printf(GREEN "Material shininess: %f\n" RESET, material->shin);
	printf(GREEN "Material reflection: %f\n" RESET, material->refl);
}

static void	ft_print_bump_map(t_bump_map *bump_map)
{
	printf(GREEN "Bump map enabled: %d\n" RESET, bump_map->enabled);
	printf(GREEN "Bump map width: %d\n" RESET, bump_map->width);
	printf(GREEN "Bump map height: %d\n" RESET, bump_map->height);
}

static void	ft_print_obj_prop(t_obj_pro *obj_prop)
{
	ft_print_material(&obj_prop->mat);
	ft_print_texture(&obj_prop->txm);
	ft_print_bump_map(&obj_prop->bpm);
}

static void	ft_print_amb_light(t_amb *amb_head)
{
	printf(YELLOW "-----amb_light-----\n" RESET);
	printf(GREEN "Ambient light ratio: %f\n" RESET, amb_head->ratio);
	printf(GREEN "Ambient light RGB: %d %d %d\n" RESET, ft_get_r(amb_head->rgb),
		ft_get_g(amb_head->rgb), ft_get_b(amb_head->rgb));
}

static void	ft_print_camera(t_cam *camera)
{
	printf(YELLOW "-----camera-----\n" RESET);
	printf(GREEN "Camera position: %f %f %f\n" RESET, camera->cord.x,
		camera->cord.y, camera->cord.z);
	printf(GREEN "Camera direction: %f %f %f\n" RESET, camera->norm.x,
		camera->norm.y, camera->norm.z);
	printf(GREEN "Camera FOV: %f\n" RESET, camera->fov);
}

static void	ft_print_light(t_light *light)
{
	int	count;

	count = 1;
	while (light)
	{
		printf(YELLOW "-----light %d-----\n" RESET, count);
		printf(GREEN "Light position: %f %f %f\n" RESET, light->cord.x,
			light->cord.y, light->cord.z);
		printf(GREEN "Light intensity: %f\n" RESET, light->ratio);
		printf(GREEN "Light RGB: %d %d %d\n" RESET, ft_get_r(light->color),
			ft_get_g(light->color), ft_get_b(light->color));
		light = light->next;
		count++;
	}
}

static void	ft_print_plane(t_plane *plane)
{
	int	count;

	count = 1;
	while (plane)
	{
		printf(YELLOW "-----plane %d-----\n" RESET, count);
		printf(GREEN "Plane position: %f %f %f\n" RESET, plane->cord.x,
			plane->cord.y, plane->cord.z);
		printf(GREEN "Plane normal: %f %f %f\n" RESET, plane->norm.x,
			plane->norm.y, plane->norm.z);
		printf(GREEN "Plane radius: %f\n" RESET, plane->radius);
		printf(GREEN "Plane RGB: %d %d %d\n" RESET,
			ft_get_r(plane->pro.txm.pri_color),
			ft_get_g(plane->pro.txm.pri_color),
			ft_get_b(plane->pro.txm.pri_color));
		ft_print_obj_prop(&plane->pro);
		plane = plane->next;
		count++;
	}
}

static void	ft_print_sphere(t_sphere *sphere)
{
	int	count;

	count = 1;
	while (sphere)
	{
		printf(YELLOW "-----sphere %d-----\n" RESET, count);
		printf(GREEN "Sphere position: %f %f %f\n" RESET, sphere->cord.x,
			sphere->cord.y, sphere->cord.z);
		printf(GREEN "Sphere radius: %f\n" RESET, sphere->diameter);
		printf(GREEN "Sphere RGB: %d %d %d\n" RESET,
			ft_get_r(sphere->pro.txm.pri_color),
			ft_get_g(sphere->pro.txm.pri_color),
			ft_get_b(sphere->pro.txm.pri_color));
		ft_print_obj_prop(&sphere->pro);
		sphere = sphere->next;
		count++;
	}
}

static void	ft_print_cylinder(t_cylinder *cylinder)
{
	int	count;

	count = 1;
	while (cylinder)
	{
		printf(YELLOW "-----cylinder %d-----\n" RESET, count);
		printf(GREEN "Cylinder position: %f %f %f\n" RESET, cylinder->cord.x,
			cylinder->cord.y, cylinder->cord.z);
		printf(GREEN "Cylinder radius: %f\n" RESET, cylinder->diameter);
		printf(GREEN "Cylinder height: %f\n" RESET, cylinder->height);
		printf(GREEN "Cylinder normal: %f %f %f\n" RESET, cylinder->norm.x,
			cylinder->norm.y, cylinder->norm.z);
		printf(GREEN "Cylinder RGB: %d %d %d\n" RESET,
			ft_get_r(cylinder->pro.txm.pri_color),
			ft_get_g(cylinder->pro.txm.pri_color),
			ft_get_b(cylinder->pro.txm.pri_color));
		ft_print_obj_prop(&cylinder->pro);
		cylinder = cylinder->next;
		count++;
	}
}

static void	ft_print_cone(t_cone *cone)
{
	int	count;

	count = 1;
	while (cone)
	{
		printf(YELLOW "-----cone %d-----\n" RESET, count);
		printf(GREEN "Cone position: %f %f %f\n" RESET, cone->cord.x,
			cone->cord.y, cone->cord.z);
		printf(GREEN "Cone height: %f\n" RESET, cone->height);
		printf(GREEN "Cone diameter: %f\n" RESET, cone->diameter);
		printf(GREEN "Cone normal: %f %f %f\n" RESET, cone->norm.x,
			cone->norm.y, cone->norm.z);
		printf(GREEN "Cone RGB: %d %d %d\n" RESET,
			ft_get_r(cone->pro.txm.pri_color),
			ft_get_g(cone->pro.txm.pri_color),
			ft_get_b(cone->pro.txm.pri_color));
		ft_print_obj_prop(&cone->pro);
		cone = cone->next;
		count++;
	}
}

static void	ft_print_master(t_master *master)
{
	printf(YELLOW "-----master-----\n" RESET);
	ft_print_amb_light(&master->amb_head);
	ft_print_camera(&master->cam_head);
	ft_print_light(master->light_head);
	if (master->plane_head)
		ft_print_plane(master->plane_head);
	if (master->sphere_head)
		ft_print_sphere(master->sphere_head);
	if (master->cylinder_head)
		ft_print_cylinder(master->cylinder_head);
	if (master->cone_head)
		ft_print_cone(master->cone_head);
}

int	main(int argc, char **argv)
{
	t_master	*master;

	if (argc == 2)
	{
		master = ft_parser(argv[1]);
		if (!master)
			return (1);
		ft_print_master(master);
		ft_render_scene(master);
		ft_free_master(master);
	}
	else
	{
		printf(RED "Error\nInvalid number of arguments\n" RESET);
		return (1);
	}
	return (0);
}
