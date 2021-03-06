#pragma once
#ifndef MODEL_GEOMETRY_H
#define MODEL_GEOMETRY_H

#include "mana/core/memoryallocator.h"
//
#include <cstorage/cstorage.h>
#include <ubermath/ubermath.h>

#include "mana/core/corecommon.h"
#include "mana/graphics/entities/model.h"
#include "mana/graphics/utilities/mesh.h"
#include "xmlnode.h"

#define NO_INDEX -1

struct RawVertexModel {
  vec3 position;
  int texture_index;
  int normal_index;
  int color_index;
  struct RawVertexModel* duplicate_vertex;
  uint32_t index;
  float length;
  struct VertexSkinData* weights_data;
};

static inline void raw_vertex_model_init(struct RawVertexModel* raw_vertex_model, uint32_t index, vec3 position, struct VertexSkinData* weights_data) {
  raw_vertex_model->texture_index = NO_INDEX;
  raw_vertex_model->normal_index = NO_INDEX;
  raw_vertex_model->color_index = NO_INDEX;
  raw_vertex_model->index = index;
  raw_vertex_model->weights_data = weights_data;
  raw_vertex_model->position = position;
  raw_vertex_model->length = vec3_magnitude(position);
  raw_vertex_model->duplicate_vertex = NULL;
};

static inline bool raw_vertex_model_is_set(struct RawVertexModel* raw_vertex_model) {
  return raw_vertex_model->texture_index != NO_INDEX && raw_vertex_model->normal_index != NO_INDEX;
}

static inline bool raw_vertex_model_has_same_texture_and_normal(struct RawVertexModel* raw_vertex_model, int texture_index_other, int normal_index_other) {
  return texture_index_other == raw_vertex_model->texture_index && normal_index_other == raw_vertex_model->normal_index;
}

struct ModelData {
  struct Vector* vertices;
  struct Vector* tex_coords;
  struct Vector* normals;
  struct Vector* colors;
  struct Vector* indices;
  struct Vector* joint_ids;
  struct Vector* vertex_weights;
};

static inline void model_data_init(struct ModelData* model_data) {
  model_data->vertices = malloc(sizeof(struct Vector));
  vector_init(model_data->vertices, sizeof(struct RawVertexModel));

  model_data->tex_coords = malloc(sizeof(struct Vector));
  vector_init(model_data->tex_coords, sizeof(vec2));

  model_data->normals = malloc(sizeof(struct Vector));
  vector_init(model_data->normals, sizeof(vec3));

  model_data->colors = malloc(sizeof(struct Vector));
  vector_init(model_data->colors, sizeof(vec3));

  model_data->indices = malloc(sizeof(struct Vector));
  vector_init(model_data->indices, sizeof(uint32_t));

  model_data->joint_ids = malloc(sizeof(struct Vector));
  vector_init(model_data->joint_ids, sizeof(ivec3));

  model_data->vertex_weights = malloc(sizeof(struct Vector));
  vector_init(model_data->vertex_weights, sizeof(vec3));
}

static inline void model_data_delete(struct ModelData* model_data) {
  vector_delete(model_data->vertex_weights);
  free(model_data->vertex_weights);

  vector_delete(model_data->joint_ids);
  free(model_data->joint_ids);

  vector_delete(model_data->indices);
  free(model_data->indices);

  vector_delete(model_data->colors);
  free(model_data->colors);

  vector_delete(model_data->normals);
  free(model_data->normals);

  vector_delete(model_data->tex_coords);
  free(model_data->tex_coords);

  vector_delete(model_data->vertices);
  free(model_data->vertices);
}

struct Mesh* geometry_loader_extract_model_data(struct XmlNode* geometry_node, struct Vector* vertex_weights, bool animated);
void geometry_loader_read_raw_data(struct ModelData* model_data, struct XmlNode* mesh_data, struct Vector* vertex_weights);
void geometry_loader_read_positions(struct ModelData* model_data, struct XmlNode* mesh_data, struct Vector* vertex_weights);
void geometry_loader_read_normals(struct ModelData* model_data, struct XmlNode* mesh_data);
void geometry_loader_read_colors(struct ModelData* model_data, struct XmlNode* mesh_data);
void geometry_loader_read_texture_coordinates(struct ModelData* model_data, struct XmlNode* mesh_data);
void geometry_loader_assemble_vertices(struct ModelData* model_data, struct XmlNode* mesh_data);
void geometry_loader_process_vertex(struct ModelData* model_data, int position_index, int normal_index, int tex_coord_index, int color_index);
float geometry_loader_convert_data_to_arrays(struct ModelData* model_data, struct Mesh* model_mesh, bool animated);
void geometry_loader_deal_with_already_processed_vertex(struct ModelData* model_data, struct RawVertexModel* previous_vertex, int new_texture_index, int new_normal_index, int new_color_index);
void geometry_loader_remove_unused_vertices(struct ModelData* model_data);

#endif  // MODEL_GEOMETRY_H
