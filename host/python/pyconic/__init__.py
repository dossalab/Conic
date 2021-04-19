import pyconic._pyconic

class Conic:
    def __init__(self):
        self._conic_fd = -1

    def open(self):
        if self._conic_fd < 0:
            self._conic_fd = _pyconic.open()
            if self._conic_fd < 0:
                raise Exception('unable to connect')
        else:
            raise Exception('already connected')

    def move(self, s1, s2, s3, s4, s5, s6):
        if self._conic_fd < 0:
            raise Exception('not connected')
        ret = _pyconic.move(self._conic_fd, s1, s2, s3, s4, s5, s6)
        if ret < 0:
            self.close()
            raise Exception('connection lost')

    def close(self):
        if self._conic_fd < 0:
            raise Exception('not connected')
        _pyconic.close(self._conic_fd)
        self._conic_fd = -1
