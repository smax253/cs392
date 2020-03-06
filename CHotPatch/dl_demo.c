#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

int main(){
    void *handle;
    void (*my_fn)();

    if ((handle = dlopen("./my_dl.so",RTLD_LAZY))==NULL){
        fprintf(stderr, "Error: cannot open './my_dl.so'. %s.\n", dlerror());
        return EXIT_FAILURE;
    }
    *(void**)(&my_fn) = dlsym(handle, "my_fn");

    printf("------ C program: Calling my_fn() the first time ------\n");
    my_fn();
    printf("-------------------------------------------------------\n");
    if(dlclose(handle)<0){
        fprintf(stderr, "Error: Cannot close './my_dl.so'. %s.\n", dlerror());
        return EXIT_FAILURE;
    }
    for(int i = 0; i<5; i++){
        sleep(1);
        printf("C program: Sleep #%d.\n",i);
    }
    if ((handle = dlopen("./my_dl.so",RTLD_LAZY))==NULL){
        fprintf(stderr, "Error: cannot open './my_dl2.so'. %s.\n", dlerror());
        return EXIT_FAILURE;
    }
    *(void**)(&my_fn) = dlsym(handle, "my_fn");

    printf("------ C program: Calling my_fn() the second time -----\n");
    my_fn();
    printf("-------------------------------------------------------\n");
    if(dlclose(handle)<0){
        fprintf(stderr, "Error: Cannot close './my_dl2.so'. %s.\n", dlerror());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
