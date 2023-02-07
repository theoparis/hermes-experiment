#include <cstdio>
#include <hermes/hermes.h>
#include <jsi/jsi.h>
#include <memory>
#include <stdexcept>

auto main() -> int {
	auto conf = facebook::hermes::hardenedHermesRuntimeConfig().rebuild();
	conf.withArrayBuffer(true);
	conf.withES6Promise(true);
	conf.withEnableEval(true);
	conf.withEnableGenerator(true);

	auto runtime = facebook::hermes::makeHermesRuntime(conf.build());

	auto console = facebook::jsi::Object{*runtime};
	auto logFunction = facebook::jsi::Function::createFromHostFunction(
		*runtime,
		facebook::jsi::PropNameID::forAscii(*runtime, "log"),
		0,
		[](
			facebook::jsi::Runtime &rt,
			const facebook::jsi::Value&,
			const facebook::jsi::Value *args,
			unsigned long count
		) {
			try {
			std::printf("%s", args[0].asString(rt).utf8(rt).c_str());	
			} catch (std::runtime_error err) {
				// TODO: handle this
			}

			return nullptr;
		}
	);
	console.setProperty(*runtime, "log", logFunction);

	runtime->global().setProperty(*runtime, "console", console);

	auto buffer = std::make_shared<facebook::jsi::StringBuffer>(
			"console.log('aesports')"
	);

	runtime->evaluateJavaScript(buffer, "bruh.js");
}
