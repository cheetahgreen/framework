#include "fw/models/StaticModel.hpp"
#include "fw/common/Filesystem.hpp"
#include "fw/internal/Logging.hpp"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

namespace fw
{

StaticModel::StaticModel(std::vector<fw::GeometryChunk> geometryChunks):
    _geometryChunks{geometryChunks}
{
}

StaticModel::~StaticModel()
{
}

const std::vector<fw::GeometryChunk>& StaticModel::getGeometryChunks() const
{
    return _geometryChunks;
}

}
