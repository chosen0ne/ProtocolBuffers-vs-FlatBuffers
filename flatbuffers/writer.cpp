/**
 *
 * @author chosen0ne(louzhenlin86@126.com)
 * @create 2015/01/15 14:18:07
 */

#include <iostream>
#include <sstream>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "Sample_generated.h"
#include "flatbuffers/flatbuffers.h"

int
main(int argc, char* argv[])
{
    flatbuffers::FlatBufferBuilder fbb;
    int count;

    count = atoi(argv[1]);

    int fd = open("buf", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        std::cout << "failed to open" << std::endl;
        return -1;
    }

    for (int i = 0; i < count; i++) {
        flatbuffers::FlatBufferBuilder fbb;
        std::ostringstream oss;
        oss << "name" << i;
        auto name = fbb.CreateString(oss.str().c_str());

        std::vector<int> addrs_vec;
        int j;
        for (j = i; j < i + 100; j++) {
            addrs_vec.push_back(j);
        }
        auto addrs = fbb.CreateVector(addrs_vec);
        auto mloc = Sample::CreateSample(fbb, i, name, i + j + 100, addrs);
        fbb.Finish(mloc);

        // write len
        int size = fbb.GetSize();
        int wlen = write(fd, &size, sizeof(size));
        if (wlen == -1) {
            std::cout << "failed to write" << std::endl;
            return -1;
        }

        wlen = write(fd, fbb.GetBufferPointer(), fbb.GetSize());
        if (wlen == -1) {
            std::cout << "failed to write" << std::endl;
            return -1;
        }
    }

    close(fd);

    return 0;
}
