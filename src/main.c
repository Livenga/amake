#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define _USE_CODE_
#include "../include/amake.h"

/* src/main.c */
static void
print_help(const char *app);
static void
print_version(const char *app);



int
main(int argc,
     char *argv[])
{
  extern char *optarg;
  static const struct option long_opt[] = {
    {"help",    no_argument,       0, 'h'},
    {"version", no_argument,       0, 'V'},
    {"c",       no_argument,       0, 'c'},
    {"tex",     no_argument,       0 ,'t'},
    {"target",  required_argument, 0, 'T'},
    {"verbose", no_argument,       0, 'v'},
    {0, 0, 0, 0},
  };

  int (*make_project)(const char *, int) = NULL;
  int opt, optindex;
  int f_help  = 0, f_ver     = 0, f_tgt = 0;
  int f_ptype = 0, f_verbose = 0;
  int f_stts  = 0;

  char target_name[128];



  if(argc < 2) {
    fprintf(stderr, "%s: \033[1;31;5mOperand Error.\033[0m\n", argv[0]);
    fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
    return EOF;
  }


  memset((void *)target_name, '\0', sizeof(char) * MAX_TARGET);


  while((opt = getopt_long(argc, argv, (const char *)"hVctvT:",
          (const struct option *)long_opt, &optindex)) != EOF) {
    switch(opt) {
      case 'h': f_help  = 1;   break;
      case 'V': f_ver   = 1;   break;
      case 'c': f_ptype = 'c';
                make_project = make_c_project;
                break;
      case 't': f_ptype = 't';
                make_project = NULL;
                //make_project = make_tex_project;
                break;

      case 'T': f_tgt  = 1;
                f_stts = conf_char_len(target_name, optarg);
                break;

      case 'v': f_verbose = 1; break;

      case '?': f_help = 1; break;
      default:  f_help = 1; break;
    }
  }

  // ヘルプとバージョンの表示
  if(f_help || f_ver) {
    if(f_help) print_help(argv[0]);
    if(f_ver)  print_version(argv[0]);
    return 0;
  }


  if(!f_tgt || f_stts != 0) {
    if(f_stts == E_TARGET_NAME)
      fprintf(stderr, "%s: ターゲット名が不正です.\n", argv[0]);
    else
      fprintf(stderr, "%s: ターゲット名が指定されていません.\n", argv[0]);
    return EOF;
  }

  if(make_project == NULL) {
    fprintf(stderr, "%s: プロジェクトの種類が指定されていません.\n", argv[0]);
    return EOF;
  }


  if(make_project)
    f_stts = make_project(target_name, f_verbose);

  return 0;
}



/**
 * @fn print_help
 * このプログラムのヘルプを表示
 *
 * @param (app) {const char *} プログラム名
 * @return      {void}
 */
static void
print_help(const char *app)
{
  printf("Usage: %s [Options]\n\n", app);
  printf("[Options]\n");
  printf("  -T, --target  作成するターゲット名\n\n");

  //printf("  -t, --tex     Tex プロジェクトの作成.\n");
  printf("  -c, --c       C言語プロジェクトの作成.\n\n");

  printf("  -h, --help    ヘルプページの表示.\n");
  printf("  -V, --version バージョンの表示.\n");
}


/**
 * @fn print_version
 * プログラムのバージョン表示
 *
 * @param (app) {const char *} プログラム名
 * @return      {void}
 */
static void
print_version(const char *app)
{
  printf("%s: Version %s 13/08/2016\n", app, AMAKE_VERSION);
}
