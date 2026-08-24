#include "storage/FSFile.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>

#include "utils/zerobuf.h"

namespace taco {

FSFile*
FSFile::Open(const std::string& path, bool o_trunc,
             bool o_direct, bool o_creat, mode_t mode) {
    // Hint: wse open(2) to obtain a file descriptor of the file for read/write.
    // The file should be opened with O_RDWR flag per specification.
    // Run "man 2 open" in the shell for details.

    //TODO implement it
    int flags = O_RDWR;
    if (o_trunc)  flags |= O_TRUNC;
    if (o_direct) flags |= O_DIRECT;
    if (o_creat)  flags |= O_CREAT;
    int fd = open(path.c_str(), flags, mode);

    if (fd < 0) {
        return nullptr;
    }

    FSFile* fs = new FSFile();
    if(!fs) {
        return nullptr;
    }
    fs->isOpened = true;
    fs->file_descriptor = fd;
    fs->fsize = lseek(fd, 0, SEEK_END);
    fs->path = path;
    fs->flags = flags;
    fs->mode = mode;
    return fs;
}

FSFile::~FSFile() {
    //TODO implement it
    this->Close();
}

bool
FSFile::Reopen() {
    //TODO implement it
    this->file_descriptor = open(path.c_str(), flags, mode);
    isOpened = true;
    this->fsize = lseek(this->file_descriptor, 0, SEEK_END);
    return true;
}

void
FSFile::Close() {
    // Hint: use close(2)
    //TODO implement it
    if (this->isOpened) {
        if (close(this->file_descriptor) < 0) {
            LOG(kWarning, "FSFile->Close: %s", strerror(errno));
        }
        isOpened = false;
        this->file_descriptor = -1;
        return ;
    }
    LOG(kWarning, "FSFile->Close: Already Closed!");
}

bool
FSFile::IsOpen() const {
    //TODO implement it
    return isOpened;
}

void
FSFile::Delete() const {
    // Hint: use unlink(2)
    //TODO implement it
    if (unlink(path.c_str()) != 0) {
        LOG(kWarning, "FSFile->Delete(%s): %s", this->path, strerror(errno));
    }
}

void
FSFile::Read(void *buf, size_t count, off_t offset) {
    // Hint: use pread(2)
    //TODO implement it
    if (offset + count > this->fsize) {
        LOG(kFatal, "Read after end of file (%d bytes @ %d > %d)", count, offset,
            this->fsize);
    }
    if (offset < 0) {
        LOG(kFatal, "Read before start of file");
    }
    ssize_t read_bytes = pread(this->file_descriptor, buf, count, offset);
    if (read_bytes != (ssize_t)count) {
        LOG(kFatal, "FSFile->Read(%d, %p, %d, %d/%d) = %d: %s",
            this->file_descriptor, buf, count, offset, this->fsize, read_bytes,
            strerror(errno));
    }
}

void
FSFile::Write(const void *buf, size_t count, off_t offset) {
    // Hint: use pwrite(2)
    //TODO implement it
    if (offset + count > this->fsize) {
        LOG(kFatal, "Write after end of file (%d bytes @ %d > %d)", count, offset,
            this->fsize);
    }
    if (offset < 0) {
        LOG(kFatal, "Write before start of file");
    }
    ssize_t written_bytes = pwrite(this->file_descriptor, buf, count, offset);
    if (written_bytes != (ssize_t)count) {
        LOG(kFatal, "FSFile->Write: %s", strerror(errno));
    }
}

void
FSFile::Allocate(size_t count) {
    // Hint: call fallocate_zerofill_fast() first to see if we can use
    // the faster fallocate(2) to extend the file.
    //
    // If it returns false and errno == EOPNOTSUPP (not supported by the file
    // system), fall back to writing `count' of zeros at the end of the file.
    // You may use g_zerobuf defined in utils/zerobuf.h as a large buffer that
    // is always all 0.
    //
    // If fallocate_zerofill_fast() returns false and errno is not either 0 or
    // EOPNOTSUPP, log a fatal error with strerror(errno) as a substring.

    //TODO implement it
    if (fallocate_zerofill_fast(this->file_descriptor, this->fsize, count)) {
        this->fsize += count;
        return;
    } else if (errno == EOPNOTSUPP || errno == 0) {
        while (count > 0) {
            size_t next = std::min(count, g_zerobuf_size);
            LOG(kInfo, "Writing %d bytes to end (currently %d)", next,
                this->fsize);
            ssize_t written_bytes =
                pwrite(this->file_descriptor, g_zerobuf, next, this->fsize);
            if (written_bytes != (ssize_t)next) {
                LOG(kFatal, "FSFile->Write: %s", strerror(errno));
            }
            count -= next;
            this->fsize += next;
            }
    } else {
        LOG(kFatal, "FSFile->Allocate: %s", strerror(errno));
    }
}

size_t
FSFile::Size() const noexcept {
    // Hint: you may obtain the file size using stat(2) FSFile::Size() is
    // frequently called to determine the file size, so you might want to cache
    // the result of stat(2) in this FSFile object (but then an
    // FSFile::Allocate() call may extend it). You may assume no one may extend
    // or shrink the file externally when the database is running.

    //TODO implement it
    return fsize;
}

void
FSFile::Flush() {
    // Hint: use fsync(2) or fdatasync(2).
    //TODO implement it

}

}   // namespace taco
