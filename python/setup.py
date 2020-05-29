from pathlib import Path
import os
import glob
from sys import platform
import shutil

from setuptools import setup, Distribution
from setuptools.command.install import install
from setuptools.command.develop import develop

with open('README.md', 'r') as fh:
    long_description = fh.read()


class Develop(develop):
    def run(self):
        self.package_data = {'griddly_python': griddly_package_data('Debug')}
        develop.run(self)


# A hack to make valid platform wheels
class BinaryDistribution(Distribution):
    def is_pure(self):
        return False

    def has_ext_modules(self):
        return True


class Install(install):
    def run(self):
        self.package_data = {'griddly_python': griddly_package_data('Release')}
        install.run(self)

    # A hack to make valid platform wheels
    def finalize_options(self):
        install.finalize_options(self)
        if self.distribution.has_ext_modules():
            self.install_lib = self.install_platlib


def griddly_package_data(config='Debug'):
    this_path = os.path.dirname(os.path.realpath(__file__))
    libs_path = os.path.realpath(this_path + f'/../{config}/bin')
    resources_path = os.path.realpath(this_path + '/../resources')

    libs_to_copy = []
    libs_to_copy = []

    if platform == 'linux' or platform == 'linux2':
        libs_to_copy.extend(glob.glob(f'{libs_path}/python_griddly*.so'))
    if platform == 'darwin':
        libs_to_copy.extend([])
    elif platform == 'win32':
        libs_to_copy.extend(glob.glob(f'{libs_path}/python_griddly*.pyd'))

    # Binary files in libraries
    griddly_package_dir = os.path.realpath(this_path + '/griddly_python/libs')

    if os.path.exists(griddly_package_dir):
        shutil.rmtree(griddly_package_dir)
    os.mkdir(griddly_package_dir)

    copied_libs = [shutil.copy(lib, griddly_package_dir) for lib in libs_to_copy]

    # Resource files
    griddly_resource_dir = os.path.realpath(this_path + '/griddly_python/resources')

    if os.path.exists(griddly_resource_dir):
        shutil.rmtree(griddly_resource_dir)
    shutil.copytree(resources_path, griddly_resource_dir)
    copied_resources = [str(f) for f in Path(griddly_resource_dir).rglob('*.*')]

    copied_files = copied_libs + copied_resources

    return copied_files


setup(
    name='griddly_python',
    version="0.0.4",
    author_email="chrisbam4d@gmail.com",
    description="Griddly Python Libraries",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/bam4d/Griddly",
    packages=['griddly_python'],
    package_data={'griddly_python': griddly_package_data('Release')},
    install_requires=[
        "numpy>=1.18.0",
        "gym==0.17.2",
        "pygame>=1.9.6",
        "matplotlib>=3.2.1"
    ],
    cmdclass={
        'develop': Develop,
        'install': Install
    },
    distclass=BinaryDistribution,

)