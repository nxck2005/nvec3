project('nvec3', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++23']
)

inc = include_directories('src')

nvec3_dep = declare_dependency(
  include_directories : inc,
  version : meson.project_version()
)

# If nvec3 is downloaded inside other n-repos, we skip building the demos/tests
# to save compile time. We only build them if working on nvec3 directly.
if not meson.is_subproject()

  # Existing test
  executable('test_vec3',
    'tests/test_vec3.cpp',
    include_directories : inc
  )

  # Sphere demo
  executable('sphere',
    'demo/sphere.cpp',
    include_directories : inc
  )
endif
