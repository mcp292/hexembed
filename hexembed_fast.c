/* AUTHOR: Michael Partridge */
/* Altered version of hexembed: https://github.com/codeplea/hexembed */

/*
 * hexembed - a simple utility to help embed files in C programs
 *
 * Copyright (c) 2010-2018 Lewis Van Winkle
 *
 * http://CodePlea.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    char *fn;
    FILE *fp;
    clock_t start, stop;
    int iter;
    char c;
    
    start = clock();
    if (argc < 2) {printf("Usage:\n\thexembed <filename>\n"); return 1;}

    fn = argv[1];
    fp = fopen(fn, "rb");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s.\n", fn);
        return 1;
    }

    /*fseek(fp, 0, SEEK_END); */
    /*const int fsize = ftell(fp); */

    /*fseek(fp, 0, SEEK_SET); */
    /*unsigned char *b = malloc(fsize); */

    /*fread(b, fsize, 1, fp); */
    /*fclose(fp); */


    printf("/* Embedded file: %s */\n", fn);    
    printf("const unsigned char *file = {\n");

    for (iter = 0; (c = fgetc(fp)) != EOF; iter++)
    {
        printf("%s0x%02x",
               (iter == 0) ? "" :
               ((iter % 16) == 0) ? ",\n" : ",", /*TODO: verify that it's 16 items */
               c);
    }

    printf("\n};\n");    
    printf("const int fsize = %d;\n", iter);

    fclose(fp);                 /*TODO: pull request to close fp */
    stop = clock();

    /* time in milliseconds */
    printf("%lf\n", (1000.0 * (stop - start)) / CLOCKS_PER_SEC);
    
    return 0;
}
