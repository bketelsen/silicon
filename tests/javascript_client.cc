#include <iostream>
#include <silicon/api.hh>
#include <silicon/backends/mimosa_serve.hh>
#include <silicon/clients/javascript_client.hh>

using namespace sl;

int main(int argc, char* argv[])
{

  std::string js_client;
  
  auto hello_api = make_api(

    @test = [] () { return D(@message = "hello world."); },
    @test2 = [] () { return D(@message = "hello world."); },
    @my_scope = D(@test2(@name) = [] (auto p) {
      return D(@message = "hello " + p.name);
      }),

    @js_client = [&] () { return js_client; }

    );

  js_client = generate_javascript_client(hello_api);

  if (argc == 2)
    sl::mimosa_json_serve(hello_api, atoi(argv[1]));
  else
    std::cerr << "Usage: " << argv[0] << " port" << std::endl;
  
}
