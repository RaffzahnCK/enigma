cc_binary(name = "enigma",
           srcs = ["enigma.cc"],
           deps = [":enigma-lib"],
)

cc_library(name = "enigma-lib",
           srcs = ["controller.cc",
                   "main-utils.cc",
                   "rotor.cc",
                   "utils.cc",
                   ],
           hdrs = ["controller.h",
                   "main-utils.h",
                   "rotor.h",
                   "utils.h"
                   ],
)
