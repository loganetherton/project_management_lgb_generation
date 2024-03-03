from setuptools import setup, Extension

exts = Extension('pm_tickets', sources=['main.cpp'])

setup(
    name='pm_tickets',
    version="0.0.1",
    ext_modules=[exts]
)
