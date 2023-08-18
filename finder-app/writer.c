#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void report_error(const char* message, const char* value){
    fprintf(stderr, message, value);        
    syslog(LOG_ERR, message, value);
}

void report_message(const char* message, const char* value){
    printf(message, value);        
    syslog(LOG_DEBUG, message, value);
}

int main(int argc, char* argv[]){
    openlog(NULL, 0, LOG_USER);

    if(argc < 2){
        report_error("First parameter missing\n", NULL);
        return EXIT_FAILURE;
    }

    if(argc < 3){
        report_error("Second parameter missing\n", NULL);
        return EXIT_FAILURE;
    }

    const char* filepath = argv[1];
    const char* content = argv[2];

    int fd;

    fd = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if(fd == -1){
        report_error("Could not create file %s\n", filepath);
        return EXIT_FAILURE;
    }

    const char* success_message = "Writing %s to %s\n";
    printf(success_message, content, filepath);        
    syslog(LOG_DEBUG, success_message, content, filepath);

    ssize_t nr;
    size_t count;
    count = strlen(content);
    nr = write(fd, content, count);
    
    if(nr == -1){
        report_error("Could not write to file %s\n", NULL);
        return EXIT_FAILURE;
    } else if (nr != count){
        report_error("Not all data could be written to file %s\n", NULL);
        return EXIT_FAILURE;
    }   

    return EXIT_SUCCESS;
}