
{
  'variables': {
      'node_module_sources': [
          "src/eio.cc",
      ],
      'node_root': '/usr/local',
      'node_root_win': 'c:\\node',
  },
  'targets': [
    {
      'target_name': 'eio',
      'product_name': 'eio',
      'type': 'loadable_module',
      'product_prefix': '',
      'product_extension':'node',
      'sources': [
        '<@(node_module_sources)',
      ],
      'defines': [
        'PLATFORM="<(OS)"',
        '_LARGEFILE_SOURCE',
        '_FILE_OFFSET_BITS=64',
      ],
      'conditions': [
        [ 'OS=="mac"', {
          'libraries': [
            '-undefined dynamic_lookup'
          ],
          'include_dirs': [
             'src/',
             '<@(node_root)/include/node',
             '<@(node_root)/include',
          ],
        }],
        [ 'OS=="win"', {
          'defines': [
            'PLATFORM="win32"',
            '_LARGEFILE_SOURCE',
            '_FILE_OFFSET_BITS=64',
            '_WINDOWS',
            'BUILDING_NODE_EXTENSION'
          ],
          'libraries': [ 
              'node.lib',
          ],
          'include_dirs': [
             '<@(node_root_win)\\deps\\v8\\include',
             '<@(node_root_win)\\src',
             '<@(node_root_win)\\deps\\uv\\include',
          ],
          'msvs_settings': {
            'VCLinkerTool': {
              'AdditionalLibraryDirectories': [
                '<@(node_root_win)\\Release\\lib',
                '<@(node_root_win)\\Release',
              ],
            },
          },
        },
      ], # windows
      ] # condition
    }, # targets
  ],
}