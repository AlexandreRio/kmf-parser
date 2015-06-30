#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "cfs/cfs-coffee.h"

#define STRING "str"
#define NUMBER "number"
#define TRUE "true"
#define FALSE "false"
#define null "null"
#define O_BEGIN "o_begin"
#define O_END "o_end"
#define A_BEGIN "a_begin"
#define A_END "a_end"
#define COMMA "comma"
#define COLON "colon"

// 1k input buffer
#define INPUT_BUFFER_MAX_SIZE 1024

struct buffer
{
  // Coffee FS file descriptor
  int fd;

  // input buffer
  char ch_buf[INPUT_BUFFER_MAX_SIZE];
  // curent position in the buffer
  char *buf_pos;

  // indicates that the buffer has reach the EOF
  bool eof;
  // number of character read from the bufferj
  int nb_read_buf;
  // size of the buffer
  size_t buf_size;
};

struct token {
  char* type;
  char* value;
};

struct token_linked_list {
  struct token *cur;
  struct token *next;
};

struct buffer b;

struct buffer create_buffer(int file)
{
  b.fd = file;
  b.eof = false;

  int r = cfs_read(file, b.ch_buf, INPUT_BUFFER_MAX_SIZE);
  if (r > 0)
  {
    b.buf_size = r;
    b.buf_pos = &b.ch_buf[0];
  }
  else
    printf("Error creating the buffer\n");


  return b;
}

char read_next_from_buffer()
{
  char ret = '\0';

  // need to load a new buffer
  if (b.nb_read_buf == b.buf_size && !b.eof)
  {
    int r = cfs_read(b.fd, b.ch_buf, INPUT_BUFFER_MAX_SIZE);
    if (r > 0)
    {
      b.buf_size = r;
      b.nb_read_buf = 0;
    }
    else
      b.eof = true;
  }

  if (!b.eof)
  {
    b.buf_pos = &b.ch_buf[b.nb_read_buf];
    b.nb_read_buf++;
    ret = *b.buf_pos;
  }

  return ret;
}

void lexer(int fd)
{
  b = create_buffer(fd);

  char c;
  while ((c = read_next_from_buffer(b)) > 0)
  {
    printf("%c", c);
  }
}
