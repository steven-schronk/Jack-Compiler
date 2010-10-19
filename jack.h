#ifndef JACK_H_
#define JACK_H_

struct settings
{
	int verbose;
	int hash;
	int code;
	int comments;
	int commands;
};

extern struct settings settings;

#endif
