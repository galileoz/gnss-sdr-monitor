/*!
 * \file channel_table_model.h
 * \brief Interface of a model for storing the channels information
 * in a table-like data structure.
 *
 * \author Álvaro Cebrián Juan, 2018. acebrianjuan(at)gmail.com
 *
 * -----------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *      Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <https://www.gnu.org/licenses/>.
 *
 * -----------------------------------------------------------------------
 */


#ifndef GNSS_SDR_MONITOR_CHANNEL_TABLE_MODEL_H_
#define GNSS_SDR_MONITOR_CHANNEL_TABLE_MODEL_H_

#include "gnss_synchro.pb.h"
#include <boost/circular_buffer.hpp>
#include <QAbstractTableModel>

class Channel_Table_Model : public QAbstractTableModel
{
public:
    Channel_Table_Model();

    void update();

    void populate_channels(const gnss_sdr::Observables *stocks);
    void populate_channel(const gnss_sdr::GnssSynchro *ch);
    void clear_channel(int ch_id);
    void clear_channels();
    QString get_signal_pretty_name(const gnss_sdr::GnssSynchro *ch);
    QList<QVariant> get_list_from_cbuf(boost::circular_buffer<double> cbuf);
    int get_columns();
    void set_buffer_size();
    int get_channel_id(int row);

    // List of virtual functions that must be implemented in a read-only table model.
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


protected:
    int columns;
    int buffer_size;
    gnss_sdr::Observables stocks;

    std::vector<int> channels_id;
    std::map<int, gnss_sdr::GnssSynchro> channels;
    std::map<int, QString> channels_signal;
    std::map<int, boost::circular_buffer<double>> channels_time;
    std::map<int, boost::circular_buffer<double>> channels_prompt_i;
    std::map<int, boost::circular_buffer<double>> channels_prompt_q;
    std::map<int, boost::circular_buffer<double>> channels_cn0;
    std::map<int, boost::circular_buffer<double>> channels_doppler;

public slots:
    gnss_sdr::GnssSynchro get_channel_data(int key);

private:
    std::map<std::string, QString> map_signal_pretty_name;
};

#endif  // GNSS_SDR_MONITOR_CHANNEL_TABLE_MODEL_H_
