{
	'conditions': [
		['OS=="win"', {
			'target_defaults': {
				'rules': [
					{
						'rule_name': 'assembler',
						'msvs_cygwin_shell': 0,
						'extension': 'asm',
						'outputs': [ '<(INTERMEDIATE_DIR)/<(RULE_INPUT_ROOT).obj', ],
						'action': [ 
							'ml64', '/c', '/Fo<(INTERMEDIATE_DIR)/<(RULE_INPUT_ROOT).obj', '<(RULE_INPUT_PATH)'
						],
						'message': 'Building assembly file <(RULE_INPUT_PATH)',
						'process_outputs_as_sources': 1,
					},
				],
			},
		}],
	],
	"targets": [{
		"target_name": "cpuid",

		'include_dirs': [
			"<!(node -e \"require('nan')\")",
			'deps/libcpuid/libcpuid'
		],

		'defines': [
			'VERSION="0.2.0"',
		],

		'sources': [
			"src/cpuid.cc",
			"deps/libcpuid/libcpuid/asm-bits.c",
			"deps/libcpuid/libcpuid/cpuid_main.c",
			"deps/libcpuid/libcpuid/libcpuid_util.c",
			"deps/libcpuid/libcpuid/rdtsc.c",
			"deps/libcpuid/libcpuid/recog_amd.c",
			"deps/libcpuid/libcpuid/recog_intel.c",
		],

		"conditions": [
			['OS=="win"', {
				'defines': [ 'WIN32', '_LIB' ],
			
				'conditions': [
					['target_arch=="x64"', {
						'sources': [ 'libcpuid/masm-x64.asm' ]
					}],
				],
			}],
			['OS=="linux"', {
				'defines': ['HAVE_STDINT_H']
			}],
		],
	}],
}
