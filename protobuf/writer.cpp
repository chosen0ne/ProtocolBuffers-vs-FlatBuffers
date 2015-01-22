/**
 * 
 * @file    writer
 * @author  chosen0ne(louzhenlin86@126.com)
 * @date    2015/01/19 17:08:01
 */

#include "protos/Sample.pb.h"

#include <string>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int fd, count;
    char buf[1024];

    count = atoi(argv[1]);
    std::cout << "count: " << count << std::endl;

    fd = open("buf", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        std::cout << "failed to open file" << std::endl;
        return -1;
    }

    Sample::Sample sample;
    for (int i = 0; i < count; i++) {
        sample.set_id(i);
        sample.set_ip(i + 100);
        sample.set_name("kobe");
        sample.clear_addr_list();
        for (int j = i; j < i + 100; j++) {
            sample.add_addr_list(j);
        }

        int size = sample.ByteSize();
        int nwritten = write(fd, &size, sizeof(size));
        if (nwritten == -1) {
            std::cout << "failed to write" << std::endl;
            return -1;
        }

        if (!sample.SerializeToArray(buf, 1024)) {
            std::cout << "failed to serialize" << std::endl;
            return -1;
        }

        nwritten = write(fd, buf, size);
        if (nwritten == -1) {
            std::cout << "failed to write" << std::endl;
            return -1;
        }
    }

    return 0;
}
