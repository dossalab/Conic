from setuptools import setup, find_packages

module = setuptools.Extension(
    "pyconic._pyconic",
    sources=[
        "host/serial_unix.c",
        "host/serial_windows.c",
        "host/libconic.c",
        "host/pyconic.c"
    ],
    include_dirs=["."],
    language="c"
)

setup(
    name = 'pyconic',
    version='1.0',
    ext_modules=[module],
    package_dir = {'': 'host/python/'},
    packages=['pyconic']
)
