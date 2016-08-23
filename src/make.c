#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

//#define _MAKE_PROJECT
#include "../include/amake.h"
//#include "../include/source.h"



/* プロトタイプ宣言 */
static char *
xstrncat(const char *parent,
         const char *child,
         size_t size);

static void *
xfree(void *ptr,
      size_t size);

static int
makedirs(const char *parent,
         const char *child,
         size_t size);



/**
 * @fn make_c_project
 * C言語プロジェクトの作成
 *
 * @param (target)    {const char *} ターゲット名
 * @param (f_verbose) {int} verbose フラグ
 * @return         {int} エラーコード及び成功は0
 */
int
make_c_project(const char *target,
               const int  f_verbose)
{
  extern const char *c_source, *c_make;

  FILE *src_fp   = NULL, *make_fp = NULL;
  int  stts      = 0;
  long path_len = 0L, make_len = 0L;
  char *src_path = NULL, *make = NULL;
 

  if((stts = mkdir(target, 0755)) < 0) {
    eprintf(stderr, "mkdir(2)", target);
    return E_MKDIR;
  }
  if(f_verbose)
    fprintf(stdout, "mkdir(2): ディレクトリ '%s' を作成しました.\n", target);

  if((stts = makedirs(target, "include", sizeof(char))) != E_MKDIR &&
      f_verbose)
    fprintf(stdout, "mkdir(2): ディレクトリ '%s/%s' を作成しました.\n",
        target, "include");
  else if(stts == E_MKDIR) return stts;

  if((stts = makedirs(target, "src", sizeof(char)) != E_MKDIR) &&
      f_verbose)
    fprintf(stdout, "mkdir(2): ディレクトリ '%s/%s' を作成しました.\n",
        target, "src");
  else if(stts == E_MKDIR) return stts;



  // main.c パス指定
  path_len = strlen(target) + strlen("src") + strlen("main.c") + 2;
  src_path = (char *)calloc(path_len, sizeof(char));
  sprintf(src_path, "%s/src/main.c", target);

  // main.c ソース
  if((src_fp = fopen(src_path, "w")) == NULL) {
    eprintf(stderr, "fopen(3)", src_path);
    goto p_error;
  }

  if(fwrite((const void *)c_source, sizeof(char), strlen(c_source), src_fp) < 0) {
    eprintf(stderr, "fwrite(3)", NULL);
    fclose(src_fp);
    goto p_error;
  }

  src_path = xfree((void *)src_path, sizeof(char) * path_len);
  fclose(src_fp);
  if(f_verbose)
    fprintf(stderr, "fwrite(3): ファイル '%s' を書き込みました.\n", src_path);


  // Makefile
  make_len = strlen(c_make) + strlen(target) - 2;
  make     = (char *)calloc(make_len, sizeof(char));
  sprintf(make, c_make, target);

  path_len = strlen(target) + strlen("Makefile") + 1;
  src_path = (char *)calloc(path_len, sizeof(char));
  sprintf(src_path, "%s/Makefile", target);


  if((make_fp = fopen(src_path, "w")) == NULL) {
    eprintf(stderr, "fopen(3)", src_path);
    make = xfree((void *)make, make_len);
    goto p_error;
  }

  if(fwrite((const void *)make, sizeof(char), strlen(make), make_fp) < 0) {
    eprintf(stderr, "fwrite(3)", NULL);
    fclose(make_fp);
    make = xfree((void *)make, sizeof(char) * strlen(make));
    goto p_error;
  }

  fclose(make_fp);
  if(f_verbose)
    fprintf(stderr, "fwrite(3): ファイル '%s' を書き込みました.\n", src_path);


  make     = xfree((void *)make,     sizeof(char) * make_len);
  src_path = xfree((void *)src_path, sizeof(char) * path_len);
  return 0;

p_error:
  src_path = xfree((void *)src_path, sizeof(char) * path_len);
  return EOF;
}


#if 0
/**
 * @fn make_tex_project
 * Texプロジェクトの作成
 *
 * @param (target)    {const char *) ターゲット名
 * @param (f_verbose) {int} verbose フラグ
 * @return         {int} エラーコード及び成功は0
 */
int
make_tex_project(const char *target,
                 const int  f_verbose)
{
  return 0;
}
#endif


/**
 * @fn makedirs
 * ディレクトリの作成
 *
 * @param (parent) {const char *} 親ディレクトリ
 * @param (child)  {const char *} 子ディレクトリ(作成するディレクトリ)
 * @return         {int} エラーコードもしくは mkdir(2) の返り値
 */
static int
makedirs(const char *parent,
         const char *child,
         size_t size)
{
  static const mode_t m_dir = 0755;
  int stts = 0;
  char *path_ptr = NULL;
  
  path_ptr = (char *)xstrncat(parent, child, size);
  if((stts = mkdir(path_ptr, m_dir)) < 0) {
    eprintf(stderr, "mkdir(2)", path_ptr);
    stts = E_MKDIR;
  }

  path_ptr = xfree((void *)path_ptr, strlen(path_ptr) * sizeof(char));
  return stts;
}



/**
 * @fn xstrncat
 * size n の領域を確保し, パスを結合
 *
 * @param (parent) {const char *} 親ディレクトリ
 * @param (child)  {const char *} 子
 * @return         {char *} 返り文字列
 */
static char *
xstrncat(const char *parent,
         const char *child,
         size_t size)
{
  char *ptr = (char *)calloc(strlen(parent) + strlen(child) + 2, size);
  if(!ptr) return NULL;

  sprintf(ptr, "%s/%s", parent, child);
  return ptr;
}


/**
 * @fn xfree
 * size 分の領域を '\0' で初期化し, ptr を解放
 *
 * @param (ptr)  {void *ptr} 解放ポインタ
 * @param (size) {size_t} サイズ
 * @return       {void *} NULL
 */
static void *
xfree(void   *ptr,
      size_t size)
{
  if(ptr) {
    memset(ptr, '\0', size);
    free(ptr);
    ptr = NULL;
  }
  return NULL;
}
