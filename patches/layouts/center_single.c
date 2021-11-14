uint
do_center(Monitor *m)
{
	int n = 0;
	Client *c;
	for (c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);

	return (
        // only center if it's globally active
        center_windows == 1
        &&
		// only center if there is only one tiled client
		(n == 1)
		&&
		// only center if that client wants to be centerd
		nexttiled(m->clients)->center_this_window
		&&
		// only center if current layout is not monocle (which fullscreens the client)
		m->lt[m->sellt]->arrange != &monocle
	);
}

void
center_single_client(Monitor *m)
{
	Client *c;
	for (c = nexttiled(m->clients); c; c = nexttiled(c->next))
		resize(
			c,
			m->mw * (1 - m->mfact) * 0.5,
			m->wy,
			m->mw * m->mfact - 2 * c->bw,
			m->wh - 2 * c->bw,
			0);
}


void
toggle_center_single()
{
    center_windows ^= 1;
    arrange(selmon);
}
