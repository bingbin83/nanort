#include "render-config.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#include "picojson.h"

#ifdef __clang__
#pragma clang diagnostic pop
#endif

#include <fstream>
#include <istream>

namespace example {

bool LoadRenderConfig(example::RenderConfig* config, const char* filename) {
  std::ifstream is(filename);
  if (is.fail()) {
    std::cerr << "Cannot open " << filename << std::endl;
    return false;
  }

  std::istream_iterator<char> input(is);
  std::string err;
  picojson::value v;
  input = picojson::parse(v, input, std::istream_iterator<char>(), &err);
  if (!err.empty()) {
    std::cerr << err << std::endl;
  }

  if (!v.is<picojson::object>()) {
    std::cerr << "Not a JSON object" << std::endl;
    return false;
  }

  picojson::object o = v.get<picojson::object>();

  if (o.find("obj_filename") != o.end()) {
    if (o["obj_filename"].is<std::string>()) {
      config->obj_filename = o["obj_filename"].get<std::string>();
    }
  }

  if (o.find("eson_filename") != o.end()) {
    if (o["eson_filename"].is<std::string>()) {
      config->eson_filename = o["eson_filename"].get<std::string>();
    }
  }

  if (o.find("bvh_filename") != o.end()) {
    if (o["bvh_filename"].is<std::string>()) {
      config->bvh_filename = o["bvh_filename"].get<std::string>();
    }
  }

  config->scene_scale = 1.0f;
  if (o.find("scene_scale") != o.end()) {
    if (o["scene_scale"].is<double>()) {
      config->scene_scale = static_cast<float>(o["scene_scale"].get<double>());
    }
  }

  config->eye[0] = 0.0f;
  config->eye[1] = 0.0f;
  config->eye[2] = 5.0f;
  if (o.find("eye") != o.end()) {
    if (o["eye"].is<picojson::array>()) {
      picojson::array arr = o["eye"].get<picojson::array>();
      if (arr.size() == 3) {
        config->eye[0] = static_cast<float>(arr[0].get<double>());
        config->eye[1] = static_cast<float>(arr[1].get<double>());
        config->eye[2] = static_cast<float>(arr[2].get<double>());
      }
    }
  }

  config->up[0] = 0.0f;
  config->up[1] = 1.0f;
  config->up[2] = 0.0f;
  if (o.find("up") != o.end()) {
    if (o["up"].is<picojson::array>()) {
      picojson::array arr = o["up"].get<picojson::array>();
      if (arr.size() == 3) {
        config->up[0] = static_cast<float>(arr[0].get<double>());
        config->up[1] = static_cast<float>(arr[1].get<double>());
        config->up[2] = static_cast<float>(arr[2].get<double>());
      }
    }
  }

  config->look_at[0] = 0.0f;
  config->look_at[1] = 0.0f;
  config->look_at[2] = 0.0f;
  if (o.find("look_at") != o.end()) {
    if (o["look_at"].is<picojson::array>()) {
      picojson::array arr = o["look_at"].get<picojson::array>();
      if (arr.size() == 3) {
        config->look_at[0] = static_cast<float>(arr[0].get<double>());
        config->look_at[1] = static_cast<float>(arr[1].get<double>());
        config->look_at[2] = static_cast<float>(arr[2].get<double>());
      }
    }
  }

  config->fov = 45.0f;
  if (o.find("fov") != o.end()) {
    if (o["fov"].is<double>()) {
      config->fov = static_cast<float>(o["fov"].get<double>());
    }
  }

  config->width = 512;
  if (o.find("width") != o.end()) {
    if (o["width"].is<double>()) {
      config->width = static_cast<int>(o["width"].get<double>());
    }
  }

  config->height = 512;
  if (o.find("height") != o.end()) {
    if (o["height"].is<double>()) {
      config->height = static_cast<int>(o["height"].get<double>());
    }
  }

  config->vdisp_space = VDISP_SPACE_WORLD;
  if (o.find("vdisp_space") != o.end()) {
    if (o["vdisp_space"].is<std::string>()) {
      std::string space = o["vdisp_space"].get<std::string>();
      if (space.compare("world") == 0) {
        config->vdisp_space = example::VDISP_SPACE_WORLD;
      } else if (space.compare("tangnet") == 0) {
        config->vdisp_space = example::VDISP_SPACE_TANGENT;
      }
    }
  }

  config->vdisp_scale = 1.0f;
  if (o.find("vdisp_scale") != o.end()) {
    if (o["vdisp_scale"].is<double>()) {
      config->vdisp_scale = static_cast<float>(o["vdisp_scale"].get<double>());
    }
  }

  if (o.find("area_weighting") != o.end()) {
    if (o["area_weighting"].is<bool>()) {
      config->area_weighting = o["area_weighting"].get<bool>();
    }
  }

  if (o.find("gen_plane") != o.end()) {
    if (o["gen_plane"].is<bool>()) {
      config->gen_plane = o["gen_plane"].get<bool>();
    }
  }

  if (o.find("u_div") != o.end()) {
    if (o["u_div"].is<double>()) {
      config->u_div = static_cast<int>(o["u_div"].get<double>());
    }
  }

  if (o.find("v_div") != o.end()) {
    if (o["v_div"].is<double>()) {
      config->v_div = static_cast<int>(o["v_div"].get<double>());
    }
  }

  if (o.find("plane_scale") != o.end()) {
    if (o["plane_scale"].is<picojson::array>()) {
      picojson::array arr = o["plane_scale"].get<picojson::array>();
      if (arr.size() == 3) {
        config->plane_scale[0] = static_cast<float>(arr[0].get<double>());
        config->plane_scale[1] = static_cast<float>(arr[1].get<double>());
        config->plane_scale[2] = static_cast<float>(arr[2].get<double>());
      }
    }
  }


  return true;
}
}
