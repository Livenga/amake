#ifndef _SOURCE_H
#define _SOURCE_H

const char *c_source =
"#include <stdio.h>\n"
"#include <string.h>\n"
"#include <stdlib.h>\n\n"
"int\n"
"main(int argc,\n"
"     char *argv[])\n"
"{\n"
"\tprintf(\"Hello World!\\n\");\n"
"\treturn 0;\n"
"}"
;

const char *tex_source =
"\\documentclass[8pt,a4j]{jreport}\n"
"\\usepackage[dvipdfmx]{graphicx,color}\n"
"\\usepackage{ulem}\n"
"\\usepackage{amssymb}\n"
"\\usepackage{amsmath}\n"
"\\usepackage{setspace}\n"
"\\setlength{\\topmargin}{-10mm}\n"
"\\setlength{\\textwidth}{150mm}\n"
"\\setlength{\\textheight}{245mm}\n"
"\\setstretch{1.3}\n"
"\\pagestyle{headings}\n"
"%%%%empty: Not Print, plains: Print Footer, headings: Print Header.\n"
"\\begin{document}\n"
"Hello World!\n"
"\\end{document}"
;
#endif
