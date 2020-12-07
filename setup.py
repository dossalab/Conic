import setuptools

with open("README.md", "r", encoding="utf-8") as fh:
    long_description = fh.read()

module = setuptools.Extension(
    "cmod._cmod",
    sources=["host/serial_unix.c", "host/serial_windows.c", "host/libconic.c"],
    include_dirs=["."],
    language="c"
)

setuptools.setup(
    name="pyconic",
    version="0.4",
    author="Roman Luitko",
    author_email="dossalab@pm.me",
    description="libconic bindings for python",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/dossalab/conic",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: GPL 3 License",
        "Operating System :: OS Independent",
    ],
    ext_modules=[module],
    packages=setuptools.find_packages(where="src"),
    python_requires=">=3.6",
    zip_safe=False,
)
