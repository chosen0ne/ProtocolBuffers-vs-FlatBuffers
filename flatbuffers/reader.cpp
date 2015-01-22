/**
 *
 * @author chosen0ne(louzhenlin86@126.com)
 * @create 2015/01/15 16:23:37
 */

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "flatbuffers/flatbuffers.h"
#include "Sample_generated.h"

#define MAX_BUF_SIZE 4096

int
main()
{
    char buf[MAX_BUF_SIZE];

    int fd = open("buf", O_RDONLY);
    if (fd == -1) {
        std::cout << "failed to open" << std::endl;
        return -1;
    }

    struct stat statinfo;
    if (fstat(fd, &statinfo) == -1) {
        std::cout << "failed to fstat" << std::endl;
        return -1;
    }
    std::cout << "file size: " << statinfo.st_size << std::endl;

    int offset = 0;
    while (true) {
        int obj_size;
        int rlen = read(fd, &obj_size, sizeof(obj_size));
        if (rlen == -1) {
            std::cout << "failed to read" << std::endl;
            return -1;
        } else if (rlen == 0) {
            std::cout << "finish read" << std::endl;
            break;
        }

        rlen = read(fd, buf, obj_size);
        if (rlen == -1) {
            std::cout << "failed to read" << std::endl;
            return -1;
        }

        auto sample = Sample::GetSample(buf);
        //std::cout << "sample=id:" << sample->id() << ", name:"
            //<< sample->name()->c_str() << ", ip:" << sample->ip()
            //<< ", addr size: " << sample->addr_list()->size() << std::endl;

    }

    close(fd);

    return 0;
}
