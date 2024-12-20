/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL
v2. You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

RC IndexMeta::init(const char *name, const std::vector<FieldMeta> &fieldmetas) {
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  for (const auto &fieldmeta : fieldmetas) {
    fields_.push_back(fieldmeta.name());
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const {
  json_value[FIELD_NAME] = name_;

  // 创建一个 Json::Value 数组来存储 fields_
  Json::Value field_array(Json::arrayValue);
  for (const auto &field : fields_) {
    field_array.append(field);
  }

  // 将数组添加到 json_value
  json_value[FIELD_FIELD_NAME] = field_array;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index) {
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELD_NAME];

  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Fields of index [%s] is not an array. json value=%s", name_value.asCString(), fields_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  std::vector<FieldMeta> field_metas;
  for (const auto &field_value : fields_value) {
    if (!field_value.isString()) {
      LOG_ERROR("Field name in index [%s] is not a string. json value=%s", name_value.asCString(), field_value.toStyledString().c_str());
      return RC::INTERNAL;
    }

    const std::string field_name = field_value.asString();
    const FieldMeta *field = table.field(field_name.c_str());
    if (nullptr == field) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    field_metas.push_back(*field);
  }

  return index.init(name_value.asCString(), field_metas);
}

const char *IndexMeta::name() const { return name_.c_str(); }

const std::string IndexMeta::field() const {
  std::ostringstream json_stream;
  json_stream << "[";

  for (size_t i = 0; i < fields_.size(); ++i) {
    json_stream << "\"" << fields_[i] << "\"";
    if (i < fields_.size() - 1) {
      json_stream << ",";
    }
  }

  json_stream << "]";
  return json_stream.str();
}

const std::vector<std::string> &IndexMeta::vec_fields() const { return fields_; }

void IndexMeta::desc(ostream &os) const {
  os << "index name=" << name_ << ", fields=[";

  // 使用迭代器遍历 fields_ vector
  for (auto it = fields_.begin(); it != fields_.end(); ++it) {
    os << *it;

    // 如果不是最后一个元素，添加逗号和空格
    if (std::next(it) != fields_.end()) {
      os << ", ";
    }
  }

  os << "]";
}
