long lseek(int fd, long offs, int whence)
{
    long ret[2];

    _llseek(fd, 0, offs, &ret[0], whence);
    return ret[0];
}

long _lseek(int fd, long offs, int whence)
{
    long ret[2];

    _llseek(fd, 0, offs, &ret[0], whence);
    return ret[0];
}

