from distutils.core import setup, Extension

setup(
    name='grupy',
    version='0.1',
    description='grupy module',
    ext_modules=[
        Extension('grupy1', sources=['module1.c']),
        Extension('grupy2', sources=['module2.c']),
        Extension('grupy3', sources=['module3.c']),
        Extension('grupy4', sources=['module4.c']),
        Extension('grupy5', sources=['module5.c']),
        Extension('grupy6', sources=['module6.c']),
    ])

