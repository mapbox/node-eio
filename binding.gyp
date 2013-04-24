{
  'conditions': [
      ['OS=="win"', {
        'variables': {
          'copy_command%': 'copy'
        },
      },{
        'variables': {
          'copy_command%': 'cp'
        },
      }]
  ],
  "targets": [
    {
      "target_name": "eio",
      "sources": [ "src/eio.cc" ]
    },
    {
      'target_name': 'action_after_build',
      'type': 'none',
      'dependencies': [ 'eio' ],
      'actions': [
        {
          'action_name': 'move_node_module',
          'inputs': [
            '<@(PRODUCT_DIR)/eio.node'
          ],
          'outputs': [
            'lib/eio.node'
          ],
          'action': ['<@(copy_command)', '<@(PRODUCT_DIR)/eio.node', 'lib/eio.node']
        }
      ]
    }

  ]
}
