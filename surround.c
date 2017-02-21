/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surround.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvan-der <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 17:29:52 by rvan-der          #+#    #+#             */
/*   Updated: 2017/02/20 19:40:55 by rvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_skin		*find_edge1(t_skin *skin)
{
	t_skin		*ret;

	if ((ret = skin)->mark == fre || skin->mark == atwallf)
	{
		while ((ret->prev)->mark == fre || (ret->prev)->mark == atwallf)
			ret = ret->prev;
		return (ret);
	}
	while (ret->mark == atwallo || ret->mark == ocp)
		ret = ret->next;
	return (ret);
}

t_skin		*find_edge2(t_skin *edge1)
{
	t_skin		*ret;

	ret = edge1;
	while ((ret->next)->mark == fre || (ret->next)->mark == atwallf)
		ret = ret->next;
	return (ret);
}

/*
int		wall_blocked(t_skin pos, t_plateau p, t_ennemi e)
{
	t_args		ag;

	set_args(pos, p, &ag);
	*(ag.l) += ag.dl;
	while (++(*(ag.c)) != ag.limc && \
			!is_ennemi((p.map)[(ag.pnt).y][(ag.pnt).x], p.pl))
		if ((p.map)[(ag.pnt).y][(ag.pnt).x] == p.pl)
			return (1);
	return (0);
}
*/

t_skin		surround_ennemi(t_plateau p, t_ennemi e, int *turn)
{
	t_skin		*edge1;
	t_skin		*edge2;
	int			dmin1;
	int			dmin2;
	int			lim;

	lim = MAX((p.size).x, (p.size).y) / 10;
	edge1 = find_edge1(e.skin);
	edge2 = find_edge2(edge1);
	dmin1 = dmin_to_wall(edge1->crd, p);
	dmin2 = dmin_to_wall(edge2->crd, p);
	(*turn)++;
	if (edge1 == edge2 || (edge2->next)->mark == atwallo)
		return (*edge1);
	if ((edge1->prev)->mark != atwallo &&
			(*turn <= lim ? (dmin1 < dmin2) : (dmin1 >= dmin2)))
		return (*edge1);
	return (*edge2);
}